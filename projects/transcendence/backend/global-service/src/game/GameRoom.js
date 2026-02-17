const PongLogic = require('./PongLogic');
const crypto = require('crypto');

class GameRoom {
	constructor(player1, player2, mode = 'quick', database, onFinish = null) {
		this.roomId = crypto.randomUUID();
		this.mode = mode; // classic or tournament
		this.db = database; //принимаем и сохраняем объект для базы данных 
		this.onFinish = onFinish;

		this.tournamentId = null;
		this.matchId = null;

		this.player1 = {
			id: player1.id,
			username: player1.username,
			socket: player1.socket,
			ready: false,
			inputs: { up: false, down: false},
			isGuest: player1.isGuest ? player1.isGuest : false,
			gameStatsId: null
		};

		this.player2 = {
			id: player2.id,
			username: player2.username,
			socket: player2.socket,
			ready: false,
			inputs: { up: false, down: false},
			isGuest: player2.isGuest ? player2.isGuest : false,
			gameStatsId: null
		};

		this.pongLogic = new PongLogic();

		this.gameLoop = null;
		this.lastUpd = Date.now();
		this.fps = 60;
		this.frameTime = 1000 / this.fps;

		//Если мы запускаем обычный матч то создаем статистику матча по game_stat

		if (!this.player1.isGuest) 
			this.player1.gameStatsId = this.db.createGameMatch(this.player1.id, this.mode, this.player2.username);
		if (!this.player2.isGuest) 
			this.player2.gameStatsId = this.db.createGameMatch(this.player2.id, this.mode, this.player1.username);

	}

	setPlayerReady(playerId) //Проставляем готовность игроков , если оба готовы то запускаем матч
	{
		if (this.player1.id === playerId)
			this.player1.ready = true;
		else if (this.player2.id === playerId)
			this.player2.ready = true;

		if (this.player1.ready === true && this.player2.ready === true && this.pongLogic.state.status === 'waiting')
			this.start();

		return this.player1.ready && this.player2.ready;
	}

	start()//Запускаем матч
	{
		this.pongLogic.start();//Просталяем в логике running
		this.lastUpd = Date.now();
	
		this.gameLoop = setInterval(() => { //Зацикливаем матч на 60 FPS
			this.update();
		}, this.frameTime);

		this.broadcast({
			type: 'gameStarted',
			data: this.getState()
		});
	}

	update() 
	{
		const now = Date.now();
		const dt = (now - this.lastUpd) / 1000;
		this.lastUpd = now;

		this.moveInputs(dt);

		this.pongLogic.update(dt);

		if (this.pongLogic.state.status === 'finished')
			this.stop();

		this.broadcast({
			type: 'gameState',
			data: this.getState()
		});
	}

	moveInputs(dt)
	{
		if (this.player1.inputs.up)
			this.pongLogic.movePlayer('p1', -1, dt);
		if (this.player1.inputs.down)
			this.pongLogic.movePlayer('p1', 1, dt);

		if (this.player2.inputs.up)
			this.pongLogic.movePlayer('p2', -1, dt);
		if (this.player2.inputs.down)
			this.pongLogic.movePlayer('p2', 1, dt);
	}

	handleInput(playerId, input)
	{
		let player = null;
//		let playerKey = null; // Пока что убрал , так как не вижу смысла на данном этапе 

		if (this.player1.id === playerId)
			player = this.player1; //playerKey = 'p1'; // убрал 
		else if (this.player2.id === playerId)
			player = this.player2; //playerKey = 'p2'; // убрал 

		if (!player)
			return;

		if (input.type === 'keydown')
		{
			if (input.key === 'up')
				player.inputs.up = true;
			else if (input.key === 'down')
				player.inputs.down = true;
		} 
		else if (input.type === 'keyup') 
		{
			if (input.key === 'up')
				player.inputs.up = false;
			else if (input.key === 'down')
				player.inputs.down = false;
		}
	}

	stop()
	{
		this.cleanup()

		this.saveResults();

		this.broadcast({
			type: 'gameFinished',
			data: this.getState()
		});

		// Освобождаем комнату сразу после завершения матча.
		if (this.onFinish)
		{
			const finish = this.onFinish;
			this.onFinish = null;
			finish(this.roomId);
		}
	}

	saveResults()
	{

		const state = this.pongLogic.state;

		if (this.player1.gameStatsId)
		{
			const res_p1 = state.winner === 'p1' ? 'win' : 'loss';
			this.db.updateGameResult(
				this.player1.gameStatsId,
				res_p1,
				state.score.p1,
				state.score.p2
			);
		}
		if (this.player2.gameStatsId)
		{
			const res_p2 = state.winner === 'p2' ? 'win' : 'loss';
			this.db.updateGameResult(
				this.player2.gameStatsId,
				res_p2,
				state.score.p2,
				state.score.p1
			);
		}
	}

	disconectUser(playerId)
	{
		if (this.pongLogic.state.status === 'running')
		{
			const winner = this.player1.id === playerId ? 'p2' : 'p1';
			this.pongLogic.state.status = 'finished';
			this.pongLogic.state.winner = winner;

			if (winner === 'p1')
				this.pongLogic.state.score.p1 = 11;
			else
				this.pongLogic.state.score.p2 = 11;
			
			this.stop();

			this.broadcast({
				type: 'playerDisconnected',
				data: {
					disconnectedPlayer: playerId,
					winner: winner
				}
			});
		}
	}

	getState()
	{
		const logicState = this.pongLogic.getState();

		return {
			roomId: this.roomId,
			mode: this.mode,
			status: logicState.status,
			player1: {
				id: this.player1.id,
				username: this.player1.username,
				ready: this.player1.ready,
				score: logicState.score.p1,
				isGuest: this.player1.isGuest
			},
			player2: {
				id: this.player2.id,
				username: this.player2.username,
				ready: this.player2.ready,
				score: logicState.score.p2,
				isGuest: this.player2.isGuest
			},
			ball: logicState.ball,
			paddles: {
				p1: logicState.players.p1,
				p2: logicState.players.p2
			},
			winner: logicState.winner ? {
				player: logicState.winner,
				username: logicState.winner === 'p1' ? this.player1.username : this.player2.username
			} : null
		};
	}

	broadcast(message)
	{
		const msgString = JSON.stringify(message);

		try {
			if (this.player1.socket && this.player1.socket.readyState === 1)
				this.player1.socket.send(msgString);
		} catch (error) {
			console.error(`Room ${this.roomId} : Error sending to player1:`, error);
		}

		try {
			if (this.player2.socket && this.player2.socket.readyState === 1)
				this.player2.socket.send(msgString);
		} catch (error) {
			console.error(`Room ${this.roomId} : Error sending to player2:`, error);
		}
	}

	hasPlayer(playerId) 
	{
		return this.player1.id === playerId || this.player2.id === playerId;
	}

	cleanup()
	{
		if (this.gameLoop) 
		{
			clearInterval(this.gameLoop);
			this.gameLoop = null;
		}
	}
}

module.exports = GameRoom;