const { checkAuth } = require('../middleware/checkAuth.js');
const { db, areFriends, isBlocked } = require('../database.js');

function getOrCreateChat(userOneId, userTwoId) {
	const id1 = Number(userOneId);
	const id2 = Number(userTwoId);

	//Sorting the IDs so we avoid to have duplicates (id1, id2) && (id2, id1)
	const [u1, u2] = id1 < id2 ? [id1, id2] : [id2, id1];

	//Checking if we already have this chat in the DB
	let chat = db.prepare(`
		SELECT id, user_one_id, user_two_id, created_at
		FROM chats
		WHERE user_one_id = ? AND user_two_id = ?
	`).get(u1, u2);

	//If not, we create a new and add it
	if (!chat) {
		const result = db.prepare(`
			INSERT OR IGNORE INTO chats (user_one_id, user_two_id) VALUES (?, ?)
		`).run(u1, u2);

		if (result.changes > 0) {
			chat = db.prepare('SELECT * FROM chats WHERE id = ?').get(result.lastInsertRowid);
		} else {
			//Another request might have created it in the meantime
			chat = db.prepare(`
				SELECT id, user_one_id, user_two_id, created_at
				FROM chats
				WHERE user_one_id = ? AND user_two_id = ?
			`).get(u1, u2);
		}
	}
	return chat;
}

function createMessage(chatId, senderId, content) {
	const result = db.prepare(`
		INSERT INTO messages (chat_id, sender_id, content)
		VALUES (?, ?, ?)
	`).run(chatId, senderId, content);

	return db.prepare(`
		SELECT m.id, m.chat_id, m.sender_id, m.content, m.created_at, u.username, u.display_name, u.avatar_url
		FROM messages m
		JOIN users u ON m.sender_id = u.id
		WHERE m.id = ?
	`).get(result.lastInsertRowid);
}

function getMessages(chatId, limit = 50, offset = 0) {
	return db.prepare(`
		SELECT m.id, m.chat_id, m.sender_id, m.content, m.created_at, u.username, u.display_name, u.avatar_url
		FROM messages m
		JOIN users u ON m.sender_id = u.id
		WHERE m.chat_id = ?
		ORDER BY m.created_at ASC
		LIMIT ? OFFSET ?
	`).all(chatId, limit, offset);
}

//Query to return list of ALL chats a user is curretly in
//Using CASE to return the info of the other user in the chat
//And using SUBQUERIES to add the last message in the chat and its timestamp
const GET_CHAT_BASE_QUERY = `
	SELECT
		c.id,
		c.created_at,
		CASE
			WHEN c.user_one_id = @uid THEN u2.id
			ELSE u1.id
		END as other_user_id,
		CASE
			WHEN c.user_one_id = @uid THEN u2.username
			ELSE u1.username
		END as other_username,
		CASE
			WHEN c.user_one_id = @uid THEN u2.display_name
			ELSE u1.display_name
		END as other_display_name,
		CASE
			WHEN c.user_one_id = @uid THEN u2.avatar_url
			ELSE u1.avatar_url
		END as other_avatar_url,

		-- Get the content of the last message in this chat
		(SELECT content FROM messages WHERE chat_id = c.id ORDER BY created_at DESC LIMIT 1) as last_message_content,

		-- Get the timestamp of the last message
		(SELECT created_at FROM messages WHERE chat_id = c.id ORDER BY created_at DESC LIMIT 1) as last_message_at,

		-- Get the "bool" is the user blocked by him or blocked him
		EXISTS ( SELECT 1 FROM blocks WHERE blocker_id = @uid AND blocked_id = (CASE WHEN c.user_one_id = @uid THEN u2.id ELSE u1.id END)) as blocked_by_me,
		EXISTS ( SELECT 1 FROM blocks WHERE blocker_id = (CASE WHEN c.user_one_id = @uid THEN u2.id ELSE u1.id END) AND blocked_id = @uid) as blocked_by_other
	FROM chats c
	JOIN users u1 ON c.user_one_id = u1.id
	JOIN users u2 ON c.user_two_id = u2.id
`;

// Returns all the chats a User is in
function getChatsForUser(userId) {
	return db.prepare(`${GET_CHAT_BASE_QUERY} WHERE c.user_one_id = @uid OR c.user_two_id = @uid ORDER BY last_message_at DESC`).all({ uid: userId });
}

// Returns a single char from the list given its ID
function getChatForUser(chatId, userId) {
	return db.prepare(`${GET_CHAT_BASE_QUERY} WHERE c.id = @chatId AND (c.user_one_id = @uid OR c.user_two_id = @uid)`).get({ chatId, uid: userId });
}

function isUserInChat(userId, chatId) {
	const chat = db.prepare('SELECT 1 FROM chats WHERE id = ? AND (user_one_id = ? OR user_two_id = ?)').get(chatId, userId, userId);
	return !!chat;
}

async function chatRoutes(fastify) {

	// Get all chats for the current user
	fastify.get('/api/chats', { preHandler: checkAuth }, async (req, reply) => {
		const chats = getChatsForUser(Number(req.user.id));
		reply.send(chats);
	});

	// Creates a chat with a specific user, returns the chat json back
	fastify.post('/api/chats/with/:userId', { preHandler: checkAuth }, async (req, reply) => {
		const otherUserId = parseInt(req.params.userId, 10);
		if (isNaN(otherUserId)) {
			return reply.code(400).send({ message: 'Invalid user ID' });
		}
		const userId = Number(req.user.id);
		if (userId === otherUserId) {
			return reply.code(400).send({ message: 'You cannot create a chat with yourself' });
		}
		if (!areFriends(userId, otherUserId)) {
			return reply.code(403).send({ message: 'You can only chat with friends' });
		}

		const chat = getOrCreateChat(userId, otherUserId);
		const fullChat = getChatForUser(chat.id, userId);
		reply.send(fullChat);
	});

	// Get all messages for a chat
	fastify.get('/api/chats/:chatId/messages', { preHandler: checkAuth }, async (req, reply) => {
		const chatId = parseInt(req.params.chatId, 10);
		if (isNaN(chatId)) {
			return reply.code(400).send({ message: 'Invalid chat ID' });
		}
		const userId = Number(req.user.id);
		if (!isUserInChat(userId, chatId)) {
			return reply.code(403).send({ message: 'You are not a participant in this chat.' });
		}

		const { limit = 50, offset = 0 } = req.query;
		const messages = getMessages(chatId, parseInt(limit, 10), parseInt(offset, 10));
		reply.send(messages);
	});

	// Send a message to a chat
	fastify.post('/api/chats/:chatId/messages', { preHandler: checkAuth }, async (req, reply) => {
		const chatId = parseInt(req.params.chatId, 10);
		if (isNaN(chatId)) {
			return reply.code(400).send({ message: 'Invalid chat ID' });
		}
		const userId = Number(req.user.id);
		if (!isUserInChat(userId, chatId)) {
			return reply.code(403).send({ message: 'You are not a participant in this chat.' });
		}
		const { content } = req.body;
		if (!content || !content.trim()) {
			return reply.code(400).send({ message: 'Message content cannot be empty' });
		}

		const chatInfo = db.prepare('SELECT user_one_id, user_two_id FROM chats WHERE id = ?').get(chatId);
		const receiverId = (chatInfo.user_one_id === userId) ? chatInfo.user_two_id : chatInfo.user_one_id;

		if (!receiverId) {
			return reply.code(500).send({ message: 'Could not find receiver' });
		}
		if (isBlocked(receiverId, userId) || isBlocked(userId, receiverId)) {
			return reply.code(403).send({ message: 'You cannot send messages to this user.' });
		}

		const message = createMessage(chatId, userId, content.trim());

		fastify.io.to(`user_${receiverId}`).emit('private_message', {
			id: message.id,
			senderId: userId,
			chatId: chatId,
			message: message.content,
			timestamp: message.created_at
		});

		// Also emit to sender's other tabs
		fastify.io.to(`user_${userId}`).emit('private_message', {
			id: message.id,
			senderId: userId,
			chatId: chatId,
			message: message.content,
			timestamp: message.created_at
		});

		reply.code(201).send(message);
	});
};

module.exports = {
	chatRoutes,
	getOrCreateChat,
	createMessage,
	getMessages,
	getChatsForUser,
	isUserInChat,
};
