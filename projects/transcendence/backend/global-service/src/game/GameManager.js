const GameRoom = require('./GameRoom.js');

class GameManager {
	constructor(database) {
		this.db = database;
		this.rooms = new Map();
		this.playerRooms = new Map();
		this.waitingQueue = [];
		this.tournamentWaiting = new Map();
		this.privateLobbies = new Map();
	}

	joinQueue(player) {
		if (this.playerRooms.has(player.id)) //Проверяем есть ли этот игрок в одном из матчей
		{
			return {
				success: false,
				error: 'Already in a game',
				roomId: this.playerRooms.get(player.id)
			};
		}

		const alreadyPlayerQueue = this.waitingQueue.find(p => p.id === player.id); // Проверяем находиться ли игрок в очереди на участие в матче
		if (alreadyPlayerQueue) {
			return {
				success: false,
				error: 'Already in queue'
			};
		}

		if (player.privateId)
		{
			const match = this.db.getPrivateMatchs(player.privateId);
			if (!match)
			{
				return {
					success: false,
					message: 'Private match not faund'
				}
			}
		}
		this.waitingQueue.push(player); //Добавляем игрока в очередь на матч

		if (player.privateId)
		{
			const partnerPrivate = this.waitingQueue.find(p => p.privateId === player.privateId && p.id !== player.id);
			if (partnerPrivate)
			{
				this.waitingQueue = this.waitingQueue.filter(p => p.id !== player.id && p.id !== partnerPrivate.id);
				return this.createRoom(player, partnerPrivate, 'private');

			}
			return {
				success: true,
				error: 'waiting',
			};
		}

		const normalPlayers = this.waitingQueue.filter(p => !p.privateId);
		if (normalPlayers.length >= 2) // Если игроков в очереди 2 то создаем матч. При этом убераем старых
		{
			const player1 = normalPlayers[0];
			const player2 = normalPlayers[1];
			this.waitingQueue = this.waitingQueue.filter(p =>
				p.id !== player1.id && p.id !== player2.id);
			return this.createRoom(player1, player2, 'quick');
		}

		return {
			success: true,
			error: 'waiting'
		};
	}

	leaveQueue(playerId) {
		const index = this.waitingQueue.findIndex(p => p.id === playerId);
		if (index !== -1)
		{
			this.waitingQueue.splice(index, 1)[0];
			return true;
		}
		return false;
	}

	createRoom(player1, player2, mode = 'quick', tournamentId = null, matchId = null)
	{
		const room = new GameRoom(player1, player2, mode, this.db, (roomId) => {
			this.removeRoom(roomId);
		});

		if (tournamentId && matchId)
		{
			room.tournamentId = tournamentId;
			room.matchId = matchId;
		}

		this.rooms.set(room.roomId, room);
		this.playerRooms.set(player1.id, room.roomId);
		this.playerRooms.set(player2.id, room.roomId);

		const state = room.getState();

		room.broadcast({
			type: 'roomCreated',
			data: state
		});

		return {
			success: true,
			status: 'created',
			roomId: room.roomId,
			room: state
		};
	}

	setPlayerReady(playerId) //Обозначаем игрока как готового к игре
	{
		const roomId = this.playerRooms.get(playerId);
		if (!roomId)
			return { success: false, error: 'Not in a room' };

		const room = this.rooms.get(roomId);
		if (!room)
			return { success: false, error: 'Room not found' };

		const allReady = room.setPlayerReady(playerId);

		room.broadcast({
			type: 'playerReady',
			data: {
				playerId: playerId,
				bothReady: allReady
			}
		});

		return {success: true, allReady};
	}

	handlePlayerInput(playerId, input)
	{
		const roomId = this.playerRooms.get(playerId);
		if (!roomId)
			return { success: false, error: 'Not in a room' };

		const room = this.rooms.get(roomId);
		if (!room)
			return { success: false, error: 'Room not found' };

		room.handleInput(playerId, input);
		return { success: true };
	}

	disconnectPlayer(playerId)
	{
		this.leaveQueue(playerId); // Убераем игрока из очереди если он в ней

		for(const [key, player] of this.tournamentWaiting.entries()) {
			if (player.id === playerId) 
			{
				this.tournamentWaiting.delete(key);
				break;
			}
		}

		for(const [privateId, lobby] of this.privateLobbies.entries()) {
			if (lobby.player1?.id === playerId || lobby.player2?.id === playerId) 
			{
				this.privateLobbies.delete(privateId);
				break;
			}
		}

		const roomId = this.playerRooms.get(playerId);
		if (roomId)
		{
			const room = this.rooms.get(roomId);
			if (room)
			{
				room.disconectUser(playerId);
				this.removeRoom(roomId);
			}
		}
	}
//Делать проверку на существование комнаты?


	removeRoom(roomId)
	{
		const room = this.rooms.get(roomId);
		if (!room)
			return;

		room.cleanup();

		this.playerRooms.delete(room.player1.id);
		this.playerRooms.delete(room.player2.id);

		// if (room.tournamentId && room.matchId) {
		// 	const key = `${room.tournamentId}_${room.matchId}`;
		// 	this.tournamentRooms.delete(key);
		// }

		this.rooms.delete(roomId);
	}
	// убрать room.cleanup(); так как он есть в  room.stop()
	//добавить в room tournamentId and matchId

	getPlayerStatus(playerId)
	{
		const roomId = this.playerRooms.get(playerId);
		if (roomId)
		{
			const room = this.rooms.get(roomId);
			if (roomId)
			{
				return {
					status: 'in game',
					room: room.getState()
				};
			}
		}

		const queue = this.waitingQueue.find(p => p.id === playerId);
		if (queue)
		{
			return {
				status: 'in queue',
				position: this.waitingQueue.findIndex(p => p.id === playerId) + 1
			};
		}

		return {
			status: 'player not found in queue and room'
		};
	}

	getDebug()
	{
		return {
			activeRooms: this.rooms.size,
			playersInGame: this.playerRooms.size,
			playersInQueue: this.waitingQueue.length,
			tournamentWaiting: this.tournamentWaiting.size
		};
	}

	joinTournamentRoom(tournamentId, matchId, player)
	{
		const key = `${tournamentId}_${matchId}`;

		if (this.playerRooms.has(player.id))
		{
			return {
				success: false,
				error: 'Already in game'
			};
		}

		const waitingPlayer = this.tournamentWaiting.get(key); //Проверяем есть ли ожидающий игрок
		if (!waitingPlayer)//Если нет то наш игрок первый и ставим его в ожидание
		{
			this.tournamentWaiting.set(key, player);

			player.socket.send(JSON.stringify({
				type: 'waitingOpponnent',
				data: { matchId, tournamentId}
			}));

			return {
				success: true,
				status: 'waiting'
			};
		}

		const player1 = waitingPlayer;
		const player2 = player;

		this.tournamentWaiting.delete(key);

		const roomCreated = this.createRoom(player1, player2, 'tournament', tournamentId, matchId);

		if (roomCreated.success)
		{
			const room = this.rooms.get(roomCreated.roomId);
			if (room)
			{
				room.broadcast({
					type: 'tournamentMatchReady',
					data: roomCreated.room
				});
			}
		}

		return roomCreated;
	}

	//Зачем в  !waitingPlayer делать player.socket.send

joinPrivateRoom(privateId, player) {
	let lobby = this.privateLobbies.get(privateId);

	// If Lobby is empty, this is the inviter
	// If lobby has 1 player already, this is the invited
	if (!lobby) {
		lobby = {
			id: privateId,
			player1: player,
			player2: null
		};
		this.privateLobbies.set(privateId, lobby);
		console.log(`[Private] Match ${privateId} created by ${player.username}`);
		return { success: true, status: 'waiting' };
	}
	
	if (lobby.player2) {
		return { success: false, error: 'Room is already full' };
	}

	// Check if player is trying to join their own lobby (refreshing page)
	if (lobby.player1.id === player.id) {
		lobby.player1 = player;
		return { success: true, status: 'waiting' };
	}

	lobby.player2 = player;
	console.log(`[Private] Match ${privateId} joined by ${player.username}`);

	// CREATE THE GAME ROOM
	const roomResult = this.createRoom(lobby.player1, lobby.player2, 'private');

	// CLEANUP
	this.privateLobbies.delete(privateId);

	if (roomResult.success) {
		return { success: true, status: 'ready' };
	} else {
		return { success: false, error: 'Failed to create game room' };
	}
}
}

module.exports = GameManager;
