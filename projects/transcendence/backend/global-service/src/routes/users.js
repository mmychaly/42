const { checkAuth } = require('../middleware/checkAuth.js');
const path = require('path');
const fs = require('fs').promises;

const {
	getUserById,
	updateUserProfile,
	updateUserAvatar,
	searchUsers,
	getUserGameStats,
	getLastMatches,
	getUserMatches,
	sendFriendRequest,
	respondToFriendRequest,
	getFriendRequests,
	getFriends,
	areFriends,
	removeFriendship,
	blockUser,
	unblockUser,
	isBlocked,
	getBlockedUsers
} = require('../database.js');
//const { request } = require('http');

module.exports = async function authUsers(fastify, options) {

	fastify.get('/api/users/me', { preHandler: checkAuth }, async (req, reply) => {
		const user = getUserById(req.user.id);

		if (!user) {
			reply.code(404);
			return { message: 'User not found' };
		}

		const statsGame = getUserGameStats(req.user.id);
		const totalGames = statsGame.total_wins + statsGame.total_losses;
		const winRate = totalGames > 0 ? statsGame.total_wins / totalGames : 0;

		const matches = getLastMatches(req.user.id, 3);
		const lastMatches = matches.map(match => ({
			id: match.id,
			mode: match.mode,
			opponentName: match.opponent_name,
			startedAt: match.started_at,
			result: match.result,
			score: match.my_score !== null ? {
				me: match.my_score,
				opponent: match.opponent_score
			} : undefined
		}));

		return {
			user: {
				id: user.id,
				username: user.username,
				displayName: user.display_name,
				avatarUrl: user.avatar_url,
				status: user.status,
				statusMessage: user.status_message,
				twofaEnabled: Boolean(user.twofa_enabled)
			},
			stats: {
				totalWins: statsGame.total_wins,
				totalLosses: statsGame.total_losses,
				winRate: winRate,
				lastMatches: lastMatches
			}
		};
	});

	fastify.get('/api/users/me/matches', { preHandler: checkAuth }, async (req, reply) => {
		const matches = getUserMatches(req.user.id);
		const payload = matches.map(match => ({
			id: match.id,
			mode: match.mode,
			opponentName: match.opponent_name,
			startedAt: match.started_at,
			result: match.result,
			score: match.my_score !== null ? {
				me: match.my_score,
				opponent: match.opponent_score
			} : undefined
		}));

		return { matches: payload };
	});


	fastify.patch('/api/users/me', { preHandler: checkAuth }, async (req, reply) => {
		const { displayName, statusMessage } = req.body;

		if (displayName === undefined && statusMessage === undefined)
		{
			reply.code(400);
			return { message: 'Nothing to update' };
		}

		const userUpdate = updateUserProfile(req.user.id, displayName, statusMessage);

		if (!userUpdate) {
			reply.code(404);
			return { message: 'User not found' };
		}

		return {
			user: {
				id: userUpdate.id,
				username: userUpdate.username,
				displayName: userUpdate.display_name,
				avatarUrl: userUpdate.avatar_url, //здесь
				status: userUpdate.status,
				statusMessage: userUpdate.status_message, //здесь
				twofaEnabled: Boolean(userUpdate.twofa_enabled)
			}
		};
	});

	fastify.post('/api/users/me/avatar', { preHandler: checkAuth }, async (req, reply) => {
		const data = await req.file(); //Получаем загруженный файл

		if (!data)
		{
			reply.code(400);
			return { message: 'No file upload' };
		}

		const allowedMimes = ['image/jpeg', 'image/jpg', 'image/png'];
		if (!allowedMimes.includes(data.mimetype))
		{
			reply.code(400);
			return { message: 'Invalid file type.'};
		}

		const buffer = await data.toBuffer();
		if (buffer.length > 5 * 1024 * 1024)
		{
			reply.code(400);
			return { message: 'File too large.'};
		}

		const uploadDir = path.join('/app/data', 'uploads', 'avatars');
		await fs.mkdir(uploadDir, { recursive: true });

		const ext = path.extname(data.filename);
		const filename = `${req.user.id}-${Date.now()}${ext}`;
		const filepath = path.join(uploadDir, filename);

		await fs.writeFile(filepath, buffer);//Создаем файл в объеме

		const avatarUrl = `/uploads/avatars/${filename}`;
		updateUserAvatar(req.user.id, avatarUrl);

		return {
			avatarUrl: avatarUrl
		};
	});

	fastify.get('/api/users/:id', { preHandler: checkAuth }, async (req, reply) => {
		const userId = parseInt(req.params.id, 10);
		const user = getUserById(userId);

		if (!user) {
			reply.code(404);
			return { message: 'User not found' };
		}

		if (isBlocked(userId, req.user.id)) {
			reply.code(403);
			return { message: `You were blocked by ${user.display_name || user.username}` };
		}

		const statsGame = getUserGameStats(userId);
		const totalGames = statsGame.total_wins + statsGame.total_losses;
		const winRate = totalGames > 0 ? statsGame.total_wins / totalGames : 0;

		return {
			user: {
				id: user.id,
				username: user.username,
				displayName: user.display_name,
				avatarUrl: user.avatar_url,
				status: user.status,
				statusMessage: user.status_message
			},
			stats: {
				totalWins: statsGame.total_wins,
				totalLosses: statsGame.total_losses,
				winRate: winRate
			}
		};
	});

	fastify.get('/api/users/search', { preHandler: checkAuth }, async (req, reply) => {
		const { query } = req.query;

		if (!query || query.trim().length === 0)
		{
			reply.code(400);
			return { message: 'Query parameter required'};
		}

		const users = searchUsers(query.trim());

		if (!users)
		{
			reply.code(500);
			return { message: 'Search failed'};
		}

		const results = users.map(user => ({
			id: user.id,
			username: user.username,
			displayName: user.display_name,
			avatarUrl: user.avatar_url,
			status: user.status,
			statusMessage: user.status_message
		}));

		return { results };
	});


	//Вывести список друзей
	fastify.get('/api/users/me/friends', { preHandler: checkAuth }, async (req, reply) => {
		const userId = req.user.id;
		const friendsList = getFriends(userId);

		if (!friendsList)
		{
			reply.code(500);
			return { message: 'Failed to fetch friends'};
		}

		const friends = friendsList.map(friend => ({
			user: {
				id: friend.id,
				username: friend.username,
				displayName: friend.display_name,
				avatarUrl: friend.avatar_url,
				status: friend.status
			},
			isOnline: friend.status === 'online'
		}));

		return { friends };
	});

	//Вывести список пользователей из черного списка
	fastify.get('/api/users/me/blocked', { preHandler: checkAuth }, async (req, reply) => {
		const userId = req.user.id;
		const blocked = getBlockedUsers(userId);

		const formatted = blocked.map(user => ({
			id: user.id,
			username: user.username,
			displayName: user.display_name,
			avatarUrl: user.avatar_url,
			status: user.status
		}));

		return { blocked: formatted };
	});

	//Отправить запрос в друзья
	fastify.post('/api/users/:id/friend-request', { preHandler: checkAuth }, async (req, reply) => {
		const toUserId = parseInt(req.params.id, 10);
		const fromUserId = req.user.id;

		if (fromUserId === toUserId)
		{
			reply.code(400);
			return { message: 'Cannot send friend request to youself'};
		}

		const targetUser = getUserById(toUserId);
		if (!targetUser)
		{
			reply.code(404);
			return { message: 'User not found'};
		}

		if (isBlocked(toUserId, fromUserId))
		{
			reply.code(403);
			return { message: `You were blocked by ${targetUser.display_name || targetUser.username}` };
		}

		if (isBlocked(fromUserId, toUserId))
		{
			reply.code(400);
			return { message: 'You blocked this user' };
		}

		const result = sendFriendRequest(fromUserId, toUserId);

		return result;
	});


	//Подтвердить или отклонить запрос
	fastify.post('/api/friend-requests/:id/respond', { preHandler: checkAuth }, async (req, reply) => {
		const userId = req.user.id;
		const requestId = parseInt(req.params.id, 10);
		const { action } = req.body;

		if (!action || !['accept', 'reject'].includes(action)){
			reply.code(400);
			return { error: 'Invalid action' };
		}

		try {
			const status = respondToFriendRequest(requestId, userId, action);
			return status;
		} catch (error)
		{
			req.log.error(error);
			reply.code(400);
			return { error: error.message };
		}
	});

	//Вывод списка запросов в друзья пользователю
	fastify.get('/api/users/me/friend-requests', { preHandler: checkAuth }, async (req, reply) => {
		const userId = req.user.id;
		const requests = getFriendRequests(userId);

		const formatted  = requests.map(req => ({
			id: req.id,
			from: {
				id: req.from_user_id,
				username: req.username,
				displayName: req.display_name,
				avatarUrl: req.avatar_url
			}
		}));

		return {requests: formatted };
	});

	//Заблокировать пользователя
	fastify.post('/api/users/:id/block', { preHandler: checkAuth }, async (req, reply) => {
		const blockedId = parseInt(req.params.id, 10);
		const blockerId = req.user.id;

		if (blockerId === blockedId)// на всякий случай))
		{
			reply.code(400);
			return { message: 'Cannot block yourself' };
		}

		const targetUser = getUserById(blockedId);
		if (!targetUser)
		{
			reply.code(404);
			return { message: 'User not found'};
		}

		blockUser(blockerId, blockedId);
		//removeFriendship(blockerId, blockedId); should we?

		return { status: 'blocked' };
	});

	//Разблокировать пользователя
	fastify.delete('/api/users/:id/block', { preHandler: checkAuth }, async (req, reply) => {
		const blockedId = parseInt(req.params.id, 10);
		const blockerId = req.user.id;

		if (blockerId === blockedId)
		{
			reply.code(400);
			return { message: 'Cannot unblock yourself' };
		}

		const targetUser = getUserById(blockedId);
		if (!targetUser)
		{
			reply.code(404);
			return { message: 'User not found'};
		}

		unblockUser(blockerId, blockedId);

		return { status: 'unblocked' };
	});
}
