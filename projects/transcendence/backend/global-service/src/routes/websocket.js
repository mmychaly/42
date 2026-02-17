const jwt = require('jsonwebtoken');
const crypto = require('crypto');
const {getUserById, getPrivateMatchs} = require('../database.js');
const { send } = require('process');

const JWT_SECRET = process.env.JWT_SECRET;
let guestCounter = -10000;

function takeGuestId() {
	return guestCounter--;
}

module.exports = async function websocketRoutes(fastify, options) {
	const { gameManager } = options;

	//Matchmaking, 2 socket
	fastify.get('/ws/game', { websocket: true }, (socket, req) => {
		let player = null;
		let authenticated = false;
		const token = req.cookies.token;

		socket.on('message', async (messageBuffer) => {
			try {
				const data = JSON.parse(messageBuffer.toString());

				if (data.type === 'auth')//Авторизация игрока
				{
					if (token)
					{
						try {
							const decoder = jwt.verify(token, JWT_SECRET);
							const user = getUserById(decoder.userId);

							if (!user)
							{
								socket.send(JSON.stringify({
									type: 'error',
									message: 'User not found'
								}));
								return;
							}

							player = {
								id: user.id,
								username: user.username,
								socket: socket,
								isGuest: false
							}

							authenticated = true;

							socket.send(JSON.stringify({
								type: 'authenticated',
								data: {
									id: player.id,
									username: player.username,
									isGuest: false
								}
							}));
							return;
						} catch (error)
						{
							socket.send(JSON.stringify({
								type: 'error',
								message: 'Invalide token'
							}));
							return;
						}
					}

					if (data.username)
					{
						const guestId = takeGuestId(); //Проверить как работает

						player = {
							id: guestId,
							username: data.username,
							socket: socket,
							isGuest: true
						}

						authenticated = true;

						socket.send(JSON.stringify({
							type: 'authenticated',
							data: {
								id: player.id,
								username: player.username,
								isGuest: true
							}
						}));
						return;
					}

					socket.send(JSON.stringify({
						type: 'error',
						message: 'Nead a token or username'
					}));
					return;
				}
				if (!authenticated)
				{
					socket.send(JSON.stringify({
						type: 'error',
						message: 'Not authenticated'
					}));
					return;
				}

				if (data.type === 'joinQueue') //Добавляем игрока в очередь
				{
					const result = gameManager.joinQueue(player);

					if (!result.success)
					{
						socket.send(JSON.stringify({
							type: 'error',
							message: result.error
						}));
						return;
					}

					if (result.error === 'waiting')
					{
						socket.send(JSON.stringify({
							type: 'joinedQueue',
							data: {
								position: result.numberPlayersInQueue,
								status: 'waiting'
							}
						}));
					}
					return;
				}

				if (data.type === 'leaveQueue')  //Покинуть очередь в игру
				{
					gameManager.leaveQueue(player.id);
					socket.send(JSON.stringify({
						type: 'leftQueue'
					}));
					return;
				}

				if (data.type === 'ready')
				{
					const res = gameManager.setPlayerReady(player.id);
					if (!res.success)
					{
						socket.send(JSON.stringify({
							type: 'error',
							message: res.error
						}));
					}
					return;
				}

				if (data.type === 'input')
				{
					const res = gameManager.handlePlayerInput(player.id, data.input);
					if (!res.success)
					{
						socket.send(JSON.stringify({
							type: 'error',
							message: res.error
						}));
					}
					return;
				}

				if (data.type === 'getStatus') {
					const status = gameManager.getPlayerStatus(player.id);
					socket.send(JSON.stringify({
						type: 'status',
						data: status
					}));
					return;
				}

				socket.send(JSON.stringify({
					type: 'error',
					message: 'Wrong message type: ' + data.type
				}));
				//Нужно ли здесь ставить return?
			} catch (error) {
				socket.send(JSON.stringify({
					type: 'error',
					message: 'Serveur error'
				}));
			}
		});

		socket.on('close', () => {
			if (player)
				gameManager.disconnectPlayer(player.id);
		});

		socket.on('error', (error) => {
			console.error('[Websocket Match Error:', error);
			if (player)
				gameManager.disconnectPlayer(player.id);
		});
	});

	fastify.get('/ws/game/local', { websocket: true}, (socket, req) => {
		let players = [];
		const token = req.cookies.token;
		const localGameId = crypto.randomUUID();

		socket.on("message", async (messageBuffer) => {
			try {
				const data = JSON.parse(messageBuffer.toString());

				if (data.type === 'auth')
				{
					if (data.player1Username && data.player2Username)
					{
						const player1 = {
							id: takeGuestId(),
							username: data.player1Username,
							socket: socket,
							isGuest: true,
							isLocal: true,
							localGameId: localGameId
						};

						const player2 = {
							id: takeGuestId(),
							username: data.player2Username,
							socket: socket,
							isGuest: true,
							isLocal: true,
							localGameId: localGameId
						};

						players = [player1, player2];

						socket.send(JSON.stringify({
							type: 'authenticated',
							data: {
								player1: {id: player1.id, username: player1.username, isGuest: true},
								player2: {id: player2.id, username: player2.username, isGuest: true}
							}
						}));

						const res = gameManager.createRoom(player1, player2, 'quick');
						//Так как у нас уже есть пара для матча то запускаем матч от сюда избегая очереди
						if (res.success)
						{
							socket.send(JSON.stringify({
								type: 'localGameCreated',
								data: res.room
							}));
						}
						return;
					}

					if (data.guestUsername && token)
					{
						try {
							const decoder = jwt.verify(token, JWT_SECRET);
							const user = getUserById(decoder.userId);

							if (!user)
							{
								socket.send(JSON.stringify({
									type: 'error',
									message: 'User not found'
								}));
								return;
							}

							const player1 = {
								id: user.id,
								username: user.username,
								socket: socket,
								isGuest: false,
								isLocal: true,
								localGameId: localGameId
							};

							const player2 = {
								id: takeGuestId(),
								username: data.guestUsername,
								socket: socket,
								isGuest: true,
								isLocal: true,
								localGameId: localGameId
							};

							players = [player1, player2];

							socket.send(JSON.stringify({
								type: 'authenticated',
								data: {
									player1: {id: player1.id, username: player1.username, isGuest: false},
									player2: {id: player2.id, username: player2.username, isGuest: true}
								}
							}));

							const res = gameManager.createRoom(player1, player2, 'quick');

							if (res.success)
							{
								socket.send(JSON.stringify({
									type: 'localGameCreated',
									data: res.room
								}));
							}
							return;
						} catch (error) {
							socket.send(JSON.stringify({
								type: 'error',
								message: 'Invalide token'
							}));
							return;
						}
					}

					socket.send(JSON.stringify({
						type: 'error',
						message: 'Need 2 players'
					}));
					return;
				}

				if (data.type === 'ready') //Ставим игроков в статус готовы и начинаем игру
				{
					if (players.length < 2)
					{
						socket.send(JSON.stringify({
							type: 'error',
							message: 'Players not auth'
						}));
						return;
					}

					const res = gameManager.setPlayerReady(players[0].id);
					const res2 = gameManager.setPlayerReady(players[1].id);

					if (!res.success || !res2.success)
					{
						socket.send(JSON.stringify({
							type: 'error',
							message: res.error
						}));
					}
					return;
				}

				if (data.type === 'input')
				{
					const { playerId, input} = data;

					if (!playerId || !input)
					{
						socket.send(JSON.stringify({
							type: 'error',
							message: 'Wrong data'
						}));
						return;
					}

					const res = gameManager.handlePlayerInput(playerId, input);

					if (!res.success)
					{
						socket.send(JSON.stringify({
							type: 'error',
							message: res.error
						}));
					}
					return;
				}

				socket.send(JSON.stringify({
					type: 'error',
					message: 'Wrong message type: ' + data.type
				}));

			} catch (error) {
				socket.send(JSON.stringify({
					type: 'error',
					message: 'Serveur error'
				}));
				return;
			}
		});

		socket.on('close', () => {
		if (players.length > 0)
			players.forEach(p => gameManager.disconnectPlayer(p.id));
		});

		socket.on('error', (error) => {
			console.error('[Websocket Match Error:', error);
			if (players.length > 0)
				players.forEach(p => gameManager.disconnectPlayer(p.id));
		});
	});

	fastify.get('/ws/tournament/:tournamentId', { websocket: true}, (socket, req) => {
		const tournamentId = parseInt(req.params.tournamentId)
		const token = req.cookies.token;
		const players = new Map();

		socket.on('message', async (buffer) => {
			try {
				const data = JSON.parse(buffer.toString());

				if (!data.participantId)
				{
					socket.send(JSON.stringify({
						type: 'error',
						message: 'Player id  need'
					}));
					return;
				}

				const participantId = parseInt(data.participantId);

				if (data.type === 'auth')
				{
					if (players.has(participantId))
					{
						socket.send(JSON.stringify({
							type: 'error',
							message: 'Player alredy auth'
						}));
						return;
					}

					if (token && !data.isGuest)
					{
						try {
							const decoder = jwt.verify(token, JWT_SECRET);
							const user = getUserById(decoder.userId);

							if (!user)
							{
								socket.send(JSON.stringify({
									type: 'error',
									message: 'User not found'
								}));
								return;
							}

							const player = {
								id: participantId,
								username: user.username,
								userId: user.id, //Но по идеи тоже самое что и participantId
								socket: socket,
								isGuest: false,
								tournamentId: tournamentId
							}

							players.set(player.id, player);

							socket.send(JSON.stringify({
								type: 'authenticated',
								data: {
									id: player.id,
									username: player.username,
									isGuest: false,
									tournamentId: tournamentId
								}
							}));
							return;
						} catch (error)
						{
							socket.send(JSON.stringify({
								type: 'error',
								message: 'Invalide token'
							}));
							return;
						}
					}

					if (data.alias)
					{
						const player = {
							id: participantId,
							username: data.alias,
							socket: socket,
							isGuest: true,
							tournamentId: tournamentId
						}

						players.set(player.id, player);

						socket.send(JSON.stringify({
							type: 'authenticated',
							data: {
								id: player.id,
								username: player.username,
								isGuest: true,
								tournamentId: tournamentId
							}
						}));
						return;
					}

					socket.send(JSON.stringify({
						type: 'error',
						message: 'Nead a token or username'
					}));
					return;
				}

				if (!players.has(participantId)) //Проверяем зарегистрирован ли игрок
				{
					socket.send(JSON.stringify({
						type: 'error',
						message: 'Error auth'
					}));
					return;
				}

				const player = players.get(participantId);

				if (data.type === 'joinMatch')
				{
					if (!data.matchId)
					{
						socket.send(JSON.stringify({
						type: 'error',
						message: 'MatchId required'
						}));
						return;
					}
					const result = gameManager.joinTournamentRoom(tournamentId, parseInt(data.matchId), player);

					if (!result.success)
					{
						socket.send(JSON.stringify({
							type: 'error',
							message: result.error
						}));
						return;
					}
					return;
				}

				if (data.type === 'ready')
				{
					const res = gameManager.setPlayerReady(player.id);
					if (!res.success)
					{
						socket.send(JSON.stringify({
							type: 'error',
							message: res.error
						}));
					}
					return;
				}

				if (data.type === 'input')
				{
					const res = gameManager.handlePlayerInput(player.id, data.input);
					if (!res.success)
					{
						socket.send(JSON.stringify({
							type: 'error',
							message: res.error
						}));
					}
					return;
				}

				socket.send(JSON.stringify({
					type: 'error',
					message: 'Wrong message type: ' + data.type
				}));

			} catch (error) {
				socket.send(JSON.stringify({
					type: 'error',
					message: 'Serveur error'
				}));
				return;
			}
		});

		socket.on('close', () => {

			if (players.size > 0)
			{
				for (const player of players.values())
				{
					gameManager.disconnectPlayer(player.id);
				}

				players.clear();
			}

		});

		socket.on('error', (error) => {
			console.error('[Websocket Match Error:', error);
			if (players.size > 0)
			{
				for (const player of players.values())
				{
					gameManager.disconnectPlayer(player.id);
				}

				players.clear();
			}
		});
	});

	fastify.get('/ws/game/private', { websocket: true }, (socket, req) => {
		let player = null;
		let authenticated = false;
		const token = req.cookies.token;

		socket.on('message', async (messageBuffer) => {
			try {
				const data = JSON.parse(messageBuffer.toString());

				// AUTHENTICATION
				if (data.type === 'auth')
				{
					if (token)
					{
						try {
							const decoder = jwt.verify(token, JWT_SECRET);
							const user = getUserById(decoder.userId);

							if (!user) {
								socket.send(JSON.stringify({ type: 'error', message: 'User not found' }));
								return;
							}

							if (!data.privateId) {
								socket.send(JSON.stringify({ type: 'error', message: 'Need privateId' }));
								return;
							}

							const match = getPrivateMatchs(data.privateId);

							if (!match) {
								socket.send(JSON.stringify({ type: 'error', message: 'Private match not found' }));
								return;
							}

							if (match.inviter_id !== user.id && match.invited_id !== user.id) {
								socket.send(JSON.stringify({ type: 'error', message: 'User not found in private match' }));
								return;
							}

							player = {
								id: user.id,
								username: user.username,
								privateId: data.privateId,
								socket: socket,
								isGuest: false
							}

							authenticated = true;

							socket.send(JSON.stringify({
								type: 'authenticated',
								data: {
									id: player.id,
									username: player.username,
									isGuest: false
								}
							}));
							return;
						} catch (error) {
							socket.send(JSON.stringify({ type: 'error', message: 'Invalid token' }));
							return;
						}
					}

					socket.send(JSON.stringify({ type: 'error', message: 'Need a token' }));
					return;
				}

				if (!authenticated) {
					socket.send(JSON.stringify({ type: 'error', message: 'Not authenticated' }));
					return;
				}

				// JOIN LOGIC
				if (data.type === 'joinQueue')
				{
					const result = gameManager.joinPrivateRoom(player.privateId, player);

					if (!result.success)
					{
						socket.send(JSON.stringify({
							type: 'error',
							message: result.error
						}));
						return;
					}

					// If status is 'waiting', this is the Inviter (Player 1)
					if (result.status === 'waiting')
					{
						socket.send(JSON.stringify({
							type: 'joinedQueue',
							data: {
								position: 1,
								status: 'waiting_for_friend'
							}
						}));
					}

					// If status is 'ready' (both players joined), the GameManager starts the match automatically
					return;
				}

				// GAME LOGIC
				if (data.type === 'ready')
				{
					const res = gameManager.setPlayerReady(player.id);
					if (!res.success) {
						socket.send(JSON.stringify({ type: 'error', message: res.error }));
					}
					return;
				}

				if (data.type === 'input')
				{
					console.log(`[Input] Pkg received from ${player.username} (ID: ${player.id})`);
					const res = gameManager.handlePlayerInput(player.id, data.input);
					console.log(`[Input] Processed result:`, res);
					if (!res.success) {
						console.error(`[Input Error] ${res.error}`); // Log errors to terminal
						socket.send(JSON.stringify({ type: 'error', message: res.error }));
					}
					return;
				}

				if (data.type === 'getStatus') {
					const status = gameManager.getPlayerStatus(player.id);
					socket.send(JSON.stringify({ type: 'status', data: status }));
					return;
				}

				socket.send(JSON.stringify({
					type: 'error',
					message: 'Wrong message type: ' + data.type
				}));

			} catch (error) {
				socket.send(JSON.stringify({
					type: 'error',
					message: 'Server error'
				}));
			}
		});

		socket.on('close', () => {
			if (player)
				gameManager.disconnectPlayer(player.id);
		});

		socket.on('error', (error) => {
			console.error('[Websocket Match Error:', error);
			if (player)
				gameManager.disconnectPlayer(player.id);
		});
	});
};

