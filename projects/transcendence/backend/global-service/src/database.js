const Database = require('better-sqlite3'); //Здесь Database я вляется ссылкой на класс переданный через модуль
const crypto = require('crypto');
const { devNull } = require('os');
const path = require('path');

const dbPath = path.join('/app/data', 'database.db'); //Сохраняем путь к базе данных

const db = new Database(dbPath); // через ссылку на класс создаем обект данного класса

const SESSION_IDLE_TIMEOUT_SECONDS = 120;

function setUserStatus(userId, status) {
	return db.prepare('UPDATE users SET status = ? WHERE id = ?').run(status, userId);
}

function hashPassword(password) {
	return crypto.createHash('sha256').update(password).digest('hex');
}

db.pragma('foreign_keys = ON');
db.pragma('journal_mode = WAL');

//status в users?
function initDatabase() {

	const checkExist = db.prepare(`
		SELECT name FROM sqlite_master
		WHERE type='table' AND name='schema_version'
	`).get();

	if (checkExist)
		return;

	db.exec(`
		CREATE TABLE IF NOT EXISTS schema_version (
		version INTEGER PRIMARY KEY,
		applied_at DATETIME DEFAULT CURRENT_TIMESTAMP
		);
		INSERT OR IGNORE INTO schema_version (version) VALUES (1);
	`);

	db.exec(`
		CREATE TABLE IF NOT EXISTS users (
		id INTEGER PRIMARY KEY,
		username TEXT UNIQUE NOT NULL,
		display_name TEXT NOT NULL,
		email TEXT UNIQUE NOT NULL,
		password TEXT NOT NULL,
		avatar_url TEXT DEFAULT NULL,
		status TEXT DEFAULT 'offline',
		status_message TEXT DEFAULT NULL,
		twofa_enabled INTEGER DEFAULT 0,
		twofa_secret TEXT DEFAULT NULL,
		twofa_temp_secret TEXT DEFAULT NULL,
		created_at DATETIME DEFAULT CURRENT_TIMESTAMP,
		modified_at DATETIME DEFAULT CURRENT_TIMESTAMP
		)
	`);

	db.exec(`
		CREATE TABLE IF NOT EXISTS sessions (
		session_id INTEGER PRIMARY KEY,
		user_id INTEGER UNIQUE NOT NULL,
		created_at DATETIME DEFAULT CURRENT_TIMESTAMP,
		expires_at DATETIME NOT NULL,
		last_seen DATETIME DEFAULT CURRENT_TIMESTAMP,
		modified_at DATETIME DEFAULT CURRENT_TIMESTAMP,
		FOREIGN KEY (user_id) REFERENCES users(id) ON DELETE CASCADE
		)
	`);

	const sessionColumns = db.prepare('PRAGMA table_info(sessions)').all();
	const hasLastSeen = sessionColumns.some((col) => col.name === 'last_seen');
	if (!hasLastSeen) {
		db.exec(`ALTER TABLE sessions ADD COLUMN last_seen DATETIME DEFAULT CURRENT_TIMESTAMP`);
	}

	const userColumns = db.prepare('PRAGMA table_info(users)').all();
	const hasTwofaEnabled = userColumns.some((col) => col.name === 'twofa_enabled');
	if (!hasTwofaEnabled) {
		db.exec(`ALTER TABLE users ADD COLUMN twofa_enabled INTEGER DEFAULT 0`);
	}
	const hasTwofaSecret = userColumns.some((col) => col.name === 'twofa_secret');
	if (!hasTwofaSecret) {
		db.exec(`ALTER TABLE users ADD COLUMN twofa_secret TEXT DEFAULT NULL`);
	}
	const hasTwofaTempSecret = userColumns.some((col) => col.name === 'twofa_temp_secret');
	if (!hasTwofaTempSecret) {
		db.exec(`ALTER TABLE users ADD COLUMN twofa_temp_secret TEXT DEFAULT NULL`);
	}

	db.exec(`
		CREATE TABLE IF NOT EXISTS game_stats (
		id INTEGER PRIMARY KEY,
		user_id INTEGER NOT NULL,
		mode TEXT NOT NULL,
		opponent_name TEXT,
		started_at DATETIME DEFAULT CURRENT_TIMESTAMP,
		completed_at DATETIME DEFAULT CURRENT_TIMESTAMP,
		modified_at DATETIME DEFAULT CURRENT_TIMESTAMP,
		status TEXT DEFAULT 'pending',
		result TEXT,
		my_score INTEGER,
		opponent_score INTEGER,
		FOREIGN KEY (user_id) REFERENCES users(id) ON DELETE CASCADE
		)
	`);

	db.exec(`
		CREATE TABLE IF NOT EXISTS friends (
		id INTEGER PRIMARY KEY,
		from_user_id INTEGER NOT NULL,
		to_user_id INTEGER NOT NULL,
		status TEXT DEFAULT 'pending',
		created_at DATETIME DEFAULT CURRENT_TIMESTAMP,
		modified_at DATETIME DEFAULT CURRENT_TIMESTAMP,
		responded_at DATETIME,
		FOREIGN KEY (from_user_id) REFERENCES users(id) ON DELETE CASCADE,
		FOREIGN KEY (to_user_id) REFERENCES users(id) ON DELETE CASCADE,
		UNIQUE(from_user_id, to_user_id)
		)
	`);

	db.exec(`
		CREATE TABLE IF NOT EXISTS blocks (
		id INTEGER PRIMARY KEY,
		blocker_id INTEGER NOT NULL,
		blocked_id INTEGER NOT NULL,
		created_at DATETIME DEFAULT CURRENT_TIMESTAMP,
		FOREIGN KEY (blocker_id) REFERENCES users(id) ON DELETE CASCADE,
		FOREIGN KEY (blocked_id) REFERENCES users(id) ON DELETE CASCADE,
		UNIQUE(blocker_id, blocked_id)
		)
	`);

	db.exec(`
        CREATE TABLE IF NOT EXISTS tournament_state (
        id INTEGER PRIMARY KEY,
        status TEXT DEFAULT 'waiting',
		currentMatchIndex INTEGER DEFAULT NULL,
		created_at DATETIME DEFAULT CURRENT_TIMESTAMP,
		modified_at DATETIME DEFAULT CURRENT_TIMESTAMP,
		completed_at DATETIME NULL
        )
    `);

	db.exec(`
        CREATE TABLE IF NOT EXISTS participant (
        id INTEGER PRIMARY KEY,
        tournament_id INTEGER NOT NULL,
        participant_id INTEGER ,
        alias TEXT DEFAULT NULL,
        created_by INTEGER DEFAULT NULL,
		created_at DATETIME DEFAULT CURRENT_TIMESTAMP,
		modified_at DATETIME DEFAULT CURRENT_TIMESTAMP,
		is_guest BOOLEAN NOT NULL DEFAULT FALSE,

		UNIQUE (tournament_id, participant_id),
		FOREIGN KEY (tournament_id) REFERENCES tournament_state(id) ON DELETE CASCADE
        )
    `);

	db.exec(`
		CREATE TABLE IF NOT EXISTS tournament_match (
		id INTEGER PRIMARY KEY,
		tournament_id INTEGER DEFAULT NULL,
		round INTEGER DEFAULT NULL,
		match_order INTEGER DEFAULT NULL,
		type TEXT DEFAULT 'regular',
		status TEXT DEFAULT 'pending',
		p1 INTEGER DEFAULT NULL,
		p2 INTEGER DEFAULT NULL,
		winner INTEGER DEFAULT NULL,
		created_at DATETIME DEFAULT CURRENT_TIMESTAMP,
		modified_at DATETIME DEFAULT CURRENT_TIMESTAMP,
		FOREIGN KEY (tournament_id) REFERENCES tournament_state(id) ON DELETE CASCADE
		)
	`);

	//LIVE CHAT
	db.exec(`
		CREATE TABLE IF NOT EXISTS chats (
			id INTEGER PRIMARY KEY,
			user_one_id INTEGER NOT NULL,
			user_two_id INTEGER NOT NULL,
			created_at DATETIME DEFAULT CURRENT_TIMESTAMP,
			FOREIGN KEY (user_one_id) REFERENCES users(id) ON DELETE CASCADE,
			FOREIGN KEY (user_two_id) REFERENCES users(id) ON DELETE CASCADE,
			UNIQUE (user_one_id, user_two_id)
		)
	`);

	db.exec(`
		CREATE TABLE IF NOT EXISTS messages (
			id INTEGER PRIMARY KEY,
			chat_id INTEGER NOT NULL,
			sender_id INTEGER NOT NULL,
			content TEXT NOT NULL,
			created_at DATETIME DEFAULT CURRENT_TIMESTAMP,
			FOREIGN KEY (chat_id) REFERENCES chats(id) ON DELETE CASCADE,
			FOREIGN KEY (sender_id) REFERENCES users(id) ON DELETE CASCADE
		)
	`);

		db.exec(`
		CREATE TABLE IF NOT EXISTS private_match (
		id INTEGER PRIMARY KEY,
		inviter_id INTEGER DEFAULT NULL,
		inviter_status TEXT DEFAULT 'pending',
		invited_id INTEGER DEFAULT NULL,
		invited_status TEXT DEFAULT 'pending',
		status TEXT DEFAULT 'pending',
		created_at DATETIME DEFAULT CURRENT_TIMESTAMP,
		modified_at DATETIME DEFAULT CURRENT_TIMESTAMP,
		FOREIGN KEY (inviter_id) REFERENCES users(id) ON DELETE CASCADE,
		FOREIGN KEY (invited_id) REFERENCES users(id) ON DELETE CASCADE
		)
	`);


	db.exec(`CREATE INDEX IF NOT EXISTS idx_friends_from ON friends(from_user_id, status)`);
	db.exec(`CREATE INDEX IF NOT EXISTS idx_friends_to ON friends(to_user_id, status)`);
	db.exec(`CREATE INDEX IF NOT EXISTS idx_blocks_blocker ON blocks(blocker_id)`);
	db.exec(`CREATE INDEX IF NOT EXISTS idx_blocks_blocked ON blocks(blocked_id)`);
	db.exec(`CREATE INDEX IF NOT EXISTS idx_messages_chat_id_created ON messages(chat_id, created_at)`);
	seedTestData();
}
//tournament_id INTEGER DEFAULT NULL, 08/01 поменял с NOT NULL to DEFAULT NULL
function getAllUsers() {
	return db.prepare('SELECT id, username, email, avatar_url, status, status_message, created_at, modified_at FROM users').all();
}

function getUserById(id) {
	return db.prepare('SELECT id, username, email, avatar_url, status, status_message, display_name, twofa_enabled, created_at, modified_at FROM users WHERE id = ?').get(id);
}

function getUserByUsername(username) {
	return db.prepare('SELECT * FROM users WHERE username = ?').get(username);
}

function getUserByEmail(email) { //Pourauoi par tout nous avons selectiones les donnes et la on affiche tout
	return db.prepare('SELECT * FROM users WHERE email = ?').get(email);
}

function createUser(username, email, password) {
	const passwordHash = hashPassword(password);
	const status = "offline"; //Si on a etabli un utilisateur il dovien online
	const displayName = username; // Для начала
	const newUser = db.prepare(`
		INSERT INTO users (username, email, password, status, display_name)
		VALUES	(?, ?, ?, ?, ?)
	`).run(username, email, passwordHash, status, displayName);

	return getUserById(newUser.lastInsertRowid)
}

function seedTestData() {
	const row = db.prepare(`SELECT COUNT(*) as count FROM users`).get();
	if (row && row.count > 0) {
		return;
	}

	const password = "1234";
	const misha = createUser("TestMisha", "misha@test.com", password);
	const artemii = createUser("TestArtemii", "artemii@test.com", password);
	const enrico = createUser("TestEnrico", "enrico@test.com", password);

	const insertMatch = db.prepare(`
		INSERT INTO game_stats (
			user_id, mode, opponent_name, started_at,
			completed_at, modified_at, status, result, my_score, opponent_score
		)
		VALUES (?, ?, ?, ?, ?, ?, 'completed', ?, ?, ?)
	`);

	const buildDate = (daysAgo, hoursAgo = 0) => {
		const date = new Date(Date.now() - daysAgo * 24 * 60 * 60 * 1000);
		date.setHours(date.getHours() - hoursAgo);
		return date.toISOString();
	};

	const addPair = (p1, p2, mode, p1Score, p2Score, startedAt) => {
		const p1Result = p1Score > p2Score ? "win" : "loss";
		const p2Result = p2Score > p1Score ? "win" : "loss";
		insertMatch.run(
			p1.id,
			mode,
			p2.username,
			startedAt,
			startedAt,
			startedAt,
			p1Result,
			p1Score,
			p2Score
		);
		insertMatch.run(
			p2.id,
			mode,
			p1.username,
			startedAt,
			startedAt,
			startedAt,
			p2Result,
			p2Score,
			p1Score
		);
	};

	addPair(misha, artemii, "quick", 11, 7, buildDate(0, 2));
	addPair(enrico, artemii, "tournament", 11, 9, buildDate(0, 5));
	addPair(misha, enrico, "quick", 6, 11, buildDate(3, 4));
	addPair(artemii, misha, "tournament", 11, 10, buildDate(6, 2));
	addPair(enrico, misha, "quick", 3, 11, buildDate(12, 1));
	addPair(artemii, enrico, "tournament", 11, 8, buildDate(20, 3));
	addPair(misha, artemii, "quick", 5, 11, buildDate(35, 2));
}

function updateUserProfile(userId, displayName, statusMessage)
{
	db.prepare(`
		UPDATE users
		SET
			display_name = COALESCE(?, display_name),
			status_message = COALESCE(?, status_message),
			modified_at = CURRENT_TIMESTAMP
		WHERE id = ?
	`).run(displayName, statusMessage, userId);

	return getUserById(userId);
}

function updateUserAvatar(userId, avatarUrl) {
	db.prepare(`
		UPDATE users
		SET avatar_url = ?, modified_at = CURRENT_TIMESTAMP
		WHERE id = ?
	`).run(avatarUrl, userId);

	return getUserById(userId);
}

function getTwofaData(userId) {
	return db.prepare(`
		SELECT twofa_enabled, twofa_secret, twofa_temp_secret
		FROM users
		WHERE id = ?
	`).get(userId);
}

function setTwofaTempSecret(userId, secret) {
	return db.prepare(`
		UPDATE users
		SET twofa_temp_secret = ?, modified_at = CURRENT_TIMESTAMP
		WHERE id = ?
	`).run(secret, userId);
}

function enableTwofa(userId, secret) {
	return db.prepare(`
		UPDATE users
		SET twofa_enabled = 1,
			twofa_secret = ?,
			twofa_temp_secret = NULL,
			modified_at = CURRENT_TIMESTAMP
		WHERE id = ?
	`).run(secret, userId);
}

function disableTwofa(userId) {
	return db.prepare(`
		UPDATE users
		SET twofa_enabled = 0,
			twofa_secret = NULL,
			twofa_temp_secret = NULL,
			modified_at = CURRENT_TIMESTAMP
		WHERE id = ?
	`).run(userId);
}

function searchUsers(query)
{
	return db.prepare(`
		SELECT id, username, display_name, avatar_url, status, status_message
		FROM users
		WHERE username LIKE ? OR display_name LIKE ?
		LIMIT 20
	`).all(`%${query}%`, `%${query}%`);
}

function deleteUser(id) {
	return db.prepare(`DELETE FROM users WHERE id = ?`).run(id);
}

function verifyPassword(user, password) {
	return user.password === hashPassword(password); // ici user c'est les donnes de table deja sorti?
}

function createSession(userId) { //userId on prend dans le table user?
	const expiresAt = new Date(Date.now() + 2 * 24 * 60 * 60 * 1000); //2 jours

	db.prepare('DELETE FROM sessions WHERE user_id = ?').run(userId);

	const newSession = db.prepare(`
		INSERT INTO sessions (user_id, expires_at, last_seen)
		VALUES (?, ?, ?)
	`).run(userId, expiresAt.toISOString(), new Date().toISOString());

	setUserStatus(userId, 'online');

	return newSession.lastInsertRowid;
}
//При создании сессии я по идеи так же должен модефицировать  статус в users переводя его в online

function getSessionUser(sessionId) {
	const stmt = db.prepare(`
		SELECT u.id, u.username, u.display_name, u.status, u.avatar_url, u.status_message, u.twofa_enabled
		FROM sessions s
		JOIN users u ON s.user_id = u.id
		WHERE s.session_id = ?
		  AND s.expires_at > datetime('now')
		  AND s.last_seen >= datetime('now', ?)
	`);

	return stmt.get(sessionId, `-${SESSION_IDLE_TIMEOUT_SECONDS} seconds`);
}

//Pourquoi on fait stmt.get(sessionId) et pas le run()
//c`est auoi u et u.id?
//FROM sessions s pourauoi qpres select on pqs fais from users si le cilone vient de users?
// comment ca fonction?

function deleteSession(sessionId) {
	const session = db.prepare('SELECT user_id FROM sessions WHERE session_id = ?').get(sessionId);

	if (session) {
		db.prepare('DELETE FROM sessions WHERE session_id = ?').run(sessionId);
		setUserStatus(session.user_id, 'offline');
	}

	return session;
}
//Здесь переводить пользователя в oflline
function cleanExpiredSessions() {

	const expiredSessions = db.prepare('SELECT user_id FROM sessions WHERE expires_at < datetime("now")').all();

	db.prepare(`DELETE FROM sessions WHERE expires_at < datetime("now")`).run();

	expiredSessions.forEach(session => {
		setUserStatus(session.user_id, 'offline');
	});

	return expiredSessions;
}
//Здесь переводить пользователя в oflline

function touchSession(sessionId) {
	return db.prepare(`
		UPDATE sessions
		SET last_seen = CURRENT_TIMESTAMP, modified_at = CURRENT_TIMESTAMP
		WHERE session_id = ?
	`).run(sessionId).changes > 0;
}

function cleanInactiveSessions(maxIdleSeconds = SESSION_IDLE_TIMEOUT_SECONDS) {
	const cutoff = `-${maxIdleSeconds} seconds`;
	const stale = db.prepare(`
		SELECT session_id, user_id
		FROM sessions
		WHERE last_seen < datetime('now', ?)
	`).all(cutoff);

	db.prepare(`
		DELETE FROM sessions
		WHERE last_seen < datetime('now', ?)
	`).run(cutoff);

	stale.forEach((session) => {
		setUserStatus(session.user_id, 'offline');
	});

	return stale;
}


//friends
function getFriends(userId)//Список друзей пользователя
{
	return db.prepare(`
		SELECT
			u.id,
			u.username,
			u.display_name,
			u.avatar_url,
			u.status
		FROM friends f
		JOIN users u ON u.id = (
			CASE
				WHEN f.from_user_id = ? THEN f.to_user_id
				ELSE f.from_user_id
			END
		)
		WHERE (f.from_user_id = ? OR f.to_user_id = ?)
			AND f.status = 'accepted'
	`).all(userId, userId, userId);
}

function areFriends(userId, friendId)//Проверка друг или вражина
{
	const result = db.prepare(`
		SELECT 1 FROM friends
		WHERE ((from_user_id = ? AND to_user_id = ?)
			OR (from_user_id = ? AND to_user_id = ?))
			AND status = 'accepted'
	`).get(userId, friendId, friendId, userId);

	return !!result;
}

function sendFriendRequest(fromUserId, toUserId) { // отправить запрос в друзья
	const existing = db.prepare(`
		SELECT status FROM friends
		WHERE (from_user_id = ? AND to_user_id = ?)
			OR (from_user_id = ? AND to_user_id = ?)
		`).get(fromUserId, toUserId, toUserId, fromUserId); // Проверяем запросы между двумя пользователями

	if (existing) {
		if (existing.status === 'accepted') {
			return { status: 'accepted', requestId: null }; //Если уже был подтвержденный запрос в друзья
		}
		if (existing.status === 'pending') {
			return { status: 'pending', requestId: null }; //Если уже есть запрос в друзья который находиться ожидании подтверждения
		}
	}

	const result = db.prepare(`
		INSERT INTO friends (from_user_id, to_user_id, status)
		VALUES (?, ?, 'pending')
	`).run(fromUserId, toUserId);

	return { status: 'pending', requestId: result.lastInsertRowid }; //Если запрос ушел то вернем pending с номером запроса , если запрос уже есть то номера запроса не будет.
}

function respondToFriendRequest(requestId, userId, action) { //Подтвердить запрос или отклонить
	const request = db.prepare(`
		SELECT from_user_id, to_user_id
		FROM friends
		WHERE id = ? AND to_user_id = ? AND status = 'pending'
	`).get(requestId, userId); //Проверяем есть ли к  пользователю запрос в стадии ожидания

	if (!request) {
		throw new Error('Request not found');
	}
	if (action === 'accept') {
		db.prepare(`
			UPDATE friends
			SET status = 'accepted', responded_at = ?, modified_at = CURRENT_TIMESTAMP
			WHERE id = ?
		`).run(new Date().toISOString(), requestId);//Если есть и ответ был положительным то обновляем статус и время подтверждения

		return { status: 'accepted' };
	} else {
		db.prepare('DELETE FROM friends WHERE id = ?').run(requestId);//Если пользователь ответил отказом , удаляем запрос и базы данных

		return { status: 'rejected' };
	}
}

function getFriendRequests(userId) // Список пользователей которые прислали запрос пользователю
{
	return db.prepare(`
		SELECT
			f.id, f.from_user_id, f.status, f.created_at, f.modified_at,
			u.username, u.display_name, u.avatar_url
		FROM friends f
		JOIN users u ON f.from_user_id = u.id
		WHERE f.to_user_id = ? AND f.status ='pending'
		ORDER BY f.created_at DESC
	`).all(userId);
}

function removeFriendship(userId, otherUserId) {
	return db.prepare(`
		DELETE FROM friends
		WHERE (from_user_id = ? AND to_user_id = ?)
		   OR (from_user_id = ? AND to_user_id = ?)
	`).run(userId, otherUserId, otherUserId, userId);
}

function blockUser(blockerId, blockedId) {
	return db.prepare(`
		INSERT OR IGNORE INTO blocks (blocker_id, blocked_id)
		VALUES (?, ?)
	`).run(blockerId, blockedId);
}

function unblockUser(blockerId, blockedId) {
	return db.prepare(`
		DELETE FROM blocks
		WHERE blocker_id = ? AND blocked_id = ?
	`).run(blockerId, blockedId);
}

function isBlocked(blockerId, blockedId) {
	const result = db.prepare(`
		SELECT 1 FROM blocks
		WHERE blocker_id = ? AND blocked_id = ?
	`).get(blockerId, blockedId);

	return !!result;
}

function getBlockedUsers(blockerId) {
	return db.prepare(`
		SELECT u.id, u.username, u.display_name, u.avatar_url, u.status
		FROM blocks b
		JOIN users u ON u.id = b.blocked_id
		WHERE b.blocker_id = ?
		ORDER BY b.created_at DESC
	`).all(blockerId);
}

function getUserGameStats(userId) {
	return db.prepare(`
		SELECT
			COUNT(CASE WHEN result = 'win' THEN 1 END) as total_wins,
			COUNT(CASE WHEN result = 'loss' THEN 1 END) as total_losses
		FROM game_stats
		WHERE user_id = ? AND result IN ('win', 'loss')
	`).get(userId);
}

function getLastMatches(userId, limit = 3) {
	return db.prepare(`
		SELECT id, mode, opponent_name, started_at, result, my_score, opponent_score, modified_at
		FROM game_stats
		WHERE user_id = ? AND status = 'completed'
		ORDER BY started_at DESC
		LIMIT ?
	`).all(userId, limit);
}

function getUserMatches(userId) {
	return db.prepare(`
		SELECT id, mode, opponent_name, started_at, result, my_score, opponent_score, modified_at
		FROM game_stats
		WHERE user_id = ? AND status = 'completed'
		ORDER BY started_at DESC
	`).all(userId);
}

function createGameMatch(userId, mode, opponentName) {

	const res = db.prepare(`
		INSERT INTO game_stats (user_id, mode, opponent_name, status, modified_at)
		VALUES (?, ?, ?, 'pending', CURRENT_TIMESTAMP)
	`).run(userId, mode, opponentName);

	return res.lastInsertRowid;
}

function updateGameResult(matchId, result, myScore, opponentScore) {
	db.prepare(`
		UPDATE game_stats
		SET result = ?, my_score = ?, opponent_score = ?,
			status = 'completed', completed_at = CURRENT_TIMESTAMP, modified_at = CURRENT_TIMESTAMP
		WHERE id = ?
	`).run(result, myScore, opponentScore, matchId);
}

function getActiveTournament()//Вывод 3х переменных таблицы
{
	return db.prepare(`
		SELECT id, status, currentMatchIndex
		FROM tournament_state
		WHERE status IN ('waiting', 'prepared', 'running')
		ORDER BY created_at DESC
		LIMIT 1
	`).get();
}

function createTournament() {

	const tournament_id = db.prepare(`
		INSERT INTO tournament_state (status, currentMatchIndex, created_at)
		VALUES (?, NULL, CURRENT_TIMESTAMP)
	`).run('waiting');

	return tournament_id.lastInsertRowid;
}

function getAllParticipants(tournamentId) {
	return db.prepare(`
		SELECT * FROM participant WHERE tournament_id = ?
	`).all(tournamentId);
}

function getParticipant(participantId) {
	return db.prepare(`
		SELECT * FROM participant WHERE participant_id = ?
	`).get(participantId);
}

function getAllMatches(tournamentId) {
	return db.prepare(`
		SELECT * FROM tournament_match WHERE tournament_id = ?
		ORDER BY round, match_order
	`).all(tournamentId);
}

function getMatche(matchId) {
	return db.prepare(`
		SELECT * FROM tournament_match WHERE id = ?
	`).get(matchId);
}

function finishedTournament(tournamentId) //Заканчиваем турнир
{
	db.prepare(`
		UPDATE tournament_state
		SET  status = 'finished', completed_at = CURRENT_TIMESTAMP, modified_at = CURRENT_TIMESTAMP
		WHERE id = ?
	`).run(tournamentId);
}

function addGuest(alias, tournamentId, creator) {
	const guest_id = db.prepare(`
		INSERT INTO participant (tournament_id, participant_id, alias, created_by, is_guest)
		VALUES (?, 0, ?, ?, TRUE )
	`).run(tournamentId, alias, creator);

	db.prepare(`
		UPDATE participant
		SET participant_id = ?
		WHERE id = ?
	`).run(-guest_id.lastInsertRowid, guest_id.lastInsertRowid);

	db.prepare(`
		UPDATE tournament_state
		SET modified_at = CURRENT_TIMESTAMP
		WHERE id = ?
	`).run(tournamentId);
}

function addUser(alias, userId, tournamentId) {
	db.prepare(`
		INSERT INTO participant (tournament_id, participant_id, alias, created_by, is_guest)
		VALUES (?, ?, ?, ?, FALSE )
	`).run(tournamentId, userId, alias, userId);

	db.prepare(`
		UPDATE tournament_state
		SET modified_at = CURRENT_TIMESTAMP
		WHERE id = ?
	`).run(tournamentId);

}

function prepareTournament(tournamentId) {
	db.prepare(`
		UPDATE tournament_state
			SET status = 'prepared', modified_at = CURRENT_TIMESTAMP
		WHERE id = ?
	`).run(tournamentId);
}

function createMatch(tournamentId, round_index, order_index, type_match, player_1, player_2) {
	db.prepare(`
		INSERT INTO tournament_match (tournament_id, round, match_order, type, status, p1, p2)
		VALUES (?, ?, ?, ?, 'pending', ?, ?)
	`).run(tournamentId, round_index, order_index, type_match, player_1, player_2);
}

function startTournament(tournamentId, firstMatchId) {
	db.prepare(`
		UPDATE tournament_state
			SET status = 'running', currentMatchIndex = 0, modified_at = CURRENT_TIMESTAMP
		WHERE id = ?
	`).run(tournamentId);

	db.prepare(`
		UPDATE tournament_match
			SET status = 'running', modified_at = CURRENT_TIMESTAMP
		WHERE id = ?
	`).run(firstMatchId);
}

function updateMatch(matchId, winner, status = 'finished') {
	db.prepare(`
		UPDATE tournament_match
		SET winner = ?, status = ?, modified_at = CURRENT_TIMESTAMP
		WHERE id = ?
	`).run(winner, status, matchId);
}

function updateMatchParticipant(matchId, position, participantId) {
	if (position === 'p1') {
		db.prepare(`
			UPDATE tournament_match
			SET p1 = ?
			WHERE id = ?
		`).run(participantId, matchId);
	} else if (position === 'p2') {
		db.prepare(`
			UPDATE tournament_match
			SET p2 = ?
			WHERE id = ?
		`).run(participantId, matchId);
	}
}

function updateIndexMatch(tournamentId, index) {
	db.prepare(`
		UPDATE tournament_state
		SET currentMatchIndex = ?, modified_at = CURRENT_TIMESTAMP
		WHERE id = ?
	`).run(index, tournamentId);
}

function createPrivateMatch(inviter_id, invited_id)
{
	const existing = db.prepare(`
		SELECT id FROM private_match
		WHERE inviter_id = ?
		AND invited_id = ?
		AND status = 'pending'
		`).get(inviter_id, invited_id);

	if (existing)
		return existing.id;

	const match = db.prepare(`
		INSERT INTO private_match (inviter_id, invited_id)
		VALUES(?, ?)
		`).run(inviter_id, invited_id);

	return match.lastInsertRowid;
}

function updateStatusPrivateMatch(match_id, type, status)
{

	const match = db.prepare(`
		SELECT status FROM private_match WHERE id = ?
	`).get(match_id);

	if (!match || match.status !== 'pending')
		return;

	if (type === 'inviter')
	{
		db.prepare(`
			UPDATE private_match
			SET inviter_status = ?, modified_at = CURRENT_TIMESTAMP
			WHERE id = ?
		`).run(status, match_id);
	}
	else if (type === 'invited')
	{
		db.prepare(`
			UPDATE private_match
			SET invited_status = ?, modified_at = CURRENT_TIMESTAMP
			WHERE id = ?
		`).run(status, match_id);
	}

	updateGeneralStatus(match_id);
}

function updateGeneralStatus(match_id)
{
	const usersStatus = db.prepare(`
		SELECT inviter_status, invited_status
		FROM private_match
		WHERE id = ?
	`).get(match_id);

	let statusUpdate  = 'pending';

	if (usersStatus.inviter_status === 'declined' || usersStatus.invited_status === 'declined')
		statusUpdate = 'declined';
	else if (usersStatus.inviter_status === 'accepted' || usersStatus.invited_status === 'accepted')
		statusUpdate = 'accepted';

	db.prepare(`
		UPDATE private_match
		SET status = ?, modified_at = CURRENT_TIMESTAMP
		WHERE id = ?
	`).run(statusUpdate , match_id);
}

function finishedPrivateMatch(match_id)
{
	db.prepare(`
		UPDATE private_match
		SET status = ?, modified_at = CURRENT_TIMESTAMP
		WHERE id = ?
	`).run('cancelled' , match_id);
}

function getAllUserPrivateMatches(user_id)
{
	return db.prepare(`
		SELECT *
		FROM private_match
		WHERE (inviter_id = ? OR invited_id = ?)
		AND status = 'pending'
		ORDER BY created_at DESC
	`).all(user_id, user_id);

}

function getPrivateMatchs(match_id)
{
	return db.prepare(`
		SELECT * FROM private_match WHERE id = ?
	`).get(match_id);
}

function getCurrentPrivateMatchs(inviter_id, invited_id)
{
	return db.prepare(`
		SELECT *
		FROM private_match
		WHERE inviter_id = ?
		AND invited_id = ?
		AND status = 'pending'
	`).get(inviter_id, invited_id);
}


module.exports = {
	db,
	initDatabase,
	getAllUsers,
	getUserById,
	getUserByUsername,
	getUserByEmail,
	createUser,
	updateUserProfile,
	updateUserAvatar,
	getTwofaData,
	setTwofaTempSecret,
	enableTwofa,
	disableTwofa,
	searchUsers,
	deleteUser,
	verifyPassword,
	createSession,
	getSessionUser,
	deleteSession,
	cleanExpiredSessions,
	cleanInactiveSessions,
	touchSession,
	setUserStatus,

	sendFriendRequest,
	respondToFriendRequest,
	getFriendRequests,
	getFriends,
	areFriends,
	removeFriendship,
	blockUser,
	unblockUser,
	isBlocked,
	getBlockedUsers,
	getUserGameStats,
	getLastMatches,
	getUserMatches,
	createGameMatch,
	updateGameResult,

	createTournament,
	createMatch,
	prepareTournament,
	startTournament,
	updateMatch,
	getActiveTournament,
	getAllParticipants,
	getParticipant,
	getAllMatches,
	finishedTournament,
	getMatche,
	addGuest,
	addUser,
	updateMatch,
	updateMatchParticipant,
	updateIndexMatch,

	createPrivateMatch,
	updateStatusPrivateMatch,
	updateGeneralStatus,
	finishedPrivateMatch,
	getAllUserPrivateMatches,
	getPrivateMatchs,
	getCurrentPrivateMatchs
};
