const GAME_W = 800;
const GAME_H = 400;
const PADDLE_W = 10;
const PADDLE_H = 60;
const BALL_SIZE = 10;
const PADDLE_SPEED = 300;
const BALL_SPEED = 300;
const MAX_SCORE = 5;

function defineDirection()
{
	return Math.random() < 0.5 ? -1 : 1;
}

class PongLogic {
	constructor()
	{
		this.reset();
	}

	reset() {
		this.state = {
			status: 'waiting',
			ball: {
				x: GAME_W / 2,
				y: GAME_H / 2,
				vx: BALL_SPEED * defineDirection(),
				vy: BALL_SPEED * defineDirection()
			},
			players: {
				p1: {y: GAME_H / 2 - PADDLE_H / 2 },
				p2: {y: GAME_H / 2 - PADDLE_H / 2 }
			},
			score: { p1: 0, p2: 0},
			winner: null
		};
	}

	start ()
	{
		if (this.state.status === 'waiting')
			this.state.status = 'running';
	}

	movePlayer(player, direction, dt)
	{
		if (this.state.status !== 'running')
			return;

		const paddle = this.state.players[player];
		if (!paddle)
			return;

		const delta = direction * PADDLE_SPEED * dt;
		paddle.y += delta;

		paddle.y = Math.max(0, Math.min(GAME_H - PADDLE_H, paddle.y));
	}

	update(dt)
	{
		if (this.state.status !== 'running')
			return;

		const ball = this.state.ball;

		ball.x += ball.vx * dt;
		ball.y += ball.vy * dt;
		
		if (ball.y <= 0 || ball.y + BALL_SIZE >= GAME_H)
			ball.vy *=-1;

		this.paddeleBallCollision();

		if (ball.x < 0)
			this.scoreAdd('p2');
		else if (ball.x > GAME_W)
			this.scoreAdd('p1');
	}

	paddeleBallCollision()
	{
		const { ball, players } = this.state;

		if (ball.x <= PADDLE_W && 
			ball.y + BALL_SIZE >= players.p1.y &&
			ball.y <= players.p1.y + PADDLE_H
		)
			ball.vx = Math.abs(ball.vx);

		if (ball.x + BALL_SIZE >= GAME_W - PADDLE_W &&
			ball.y + BALL_SIZE >= players.p2.y &&
			ball.y <= players.p2.y + PADDLE_H
		)
			ball.vx = -Math.abs(ball.vx);
	}

	scoreAdd(player)
	{
		this.state.score[player]++;

		if (this.state.score[player] >= MAX_SCORE)
		{
			this.state.status = 'finished';
			this.state.winner = player;
			return;
		}

		this.state.ball.x = GAME_W / 2;
		this.state.ball.y = GAME_H / 2;
		this.state.ball.vx = BALL_SPEED * defineDirection();
		this.state.ball.vy = BALL_SPEED * defineDirection();
	}

	getState()
	{
		return JSON.parse(JSON.stringify(this.state));
	}
}

module.exports = PongLogic;