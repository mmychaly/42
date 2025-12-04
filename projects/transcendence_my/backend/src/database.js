const Database = require('better-sqlite3'); //Здесь Database я вляется ссылкой на класс переданный через модуль
const crypto = require('crypto');
const { exists } = require('fs');
const path = require('path');
const { getUserByUsername } = require('../../temp/database');

const dbPath = path.join('/app/data', 'database.db'); //Сохраняем путь к базе данных
const db = new Database(dbPath); // через ссылку на класс создаем обект данного класса

function hashPassword(password) {
	return crypto.createHash('sha256').update(password).digest('hex');
}

db.pragma('foreign_keys = ON');

//status в users? 
function initDatabase() {
	

	db.exec(`
		CREATE TABLE IF NOT EXISTS users (
		id TEXT PRIMARY KEY,
		username TEXT UNIQUE NOT NULL,
		email TEXT UNIQUE NOT NULL,
		password TEXT NOT NULL,
		status TEXT DEFAULT 'offline',
		created_at DATETIME DEFAULT CURRENT_TIMESTAMP
		)
	`);

	db.exec(`
		CREATE TABLE IF NOT EXISTS sessions (
		sessions_id TEXT PRIMARY KEY,
		user_id TEXT UNIQUE NOT NULL,
		created_at DATETIME DEFAULT CURRENT_TIMESTAMP,
		expires_at DATETIME NOT NULL,
		FOREIGN KEY (user_id) REFERENCES users(id) ON DELETE CASCADE 
		)
	`);
}

function getAllUsers() {
	return db.prepare('SELECT id, username, email, status, created_at FROM users').all();
}

function getUserById(id) {
	return db.prepare('SELECT id, username, email, status, created_at FROM users WHERE id = ?').get(id);

}

function getUserByEmail(email) { //Pourauoi par tout nous avons selectiones les donnes et la on affiche tout
	return db.prepare('SELECT * FROM users WHER email = ?').get(email);
}

function createUser(username, email, password) {
	const id = crypto.randomUUID();
	const passwordHash = hashPassword(password);
	const status = "online"; //Si on a etabli un utilisateur il dovien online
	const newUser = db.prepare(`
		INSERT INTO users (id, username, email, password, status) //Add status online?
		VALUES	(?, ?, ?, ?, ?)
	`);

	newUser.run(id, username, email, passwordHash, status);//status ici?
	return getUserById(id);
}

function deletUser(id) {
	return db.prepare(`DELETE FROM users WHERE id = ?`).run(id);
}

function verifyPassword(user, password)
{
	return user.password === hashPassword(password); // ici user c'est les donnes de table deja sorti?
}

function createSession(userId) { //userId on prend dans le table user?
	const sessionId = crypto.randomUUID();
	const expiresAt = new Date(Date.now() + 2 * 24 * 60 * 60 * 1000); //2 jours

	const newSession = db.prepare(`
		INSERT INTO sessions (session_id, user_id, expires_at)
		VALUES (?, ?, ?)
	`);

	newSession.run(sessionId, userId, expiresAt.toISOString()); //c'est quoi toISOString?

	return sessionId;
}

function getSessionUser(sessionId) {
	const stmt = db.prepare(` 
		SELECT u.id, u.username, u.status
		FROM sessions s
		JOIN users u ON s.user_id = u.id
		WHERE s.ssession_id = ? AND s.expires_at > datetime(`now`)
	`);

	return stmt.get(sessionId);
}

//Pourquoi on fait stmt.get(sessionId) et pas le stmt.run()
//c`est auoi u et u.id? 
//FROM sessions s pourauoi qpres select on pqs fais from users si le cilone vient de users?
// comment ca fonction?

function deleteSession(sessionId) {
	return db.prepare(`DELETE FROM sessions WHERE session_id = ?`).run(sessionId);
}

function cleanExpiredSessions() {
	return db.prepare(`DELETE FROM sessions WHERE expires_at < datetime("now")`).run();
}

module.exports = {
	initDatabase,
	getAllUsers,
	getUserById,
	getUserByUsername,
	getUserByEmail,
	createUser,
	deletUser,
	verifyPassword,
	createSession,
	getSessionUser,
	deleteSession,
	cleanExpiredSessions
};