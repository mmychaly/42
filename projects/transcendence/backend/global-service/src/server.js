require('dotenv').config(); //Добавляем доступ к .env

const fastify = require("fastify")({ logger: true }); //Создаем сервер добавив модуль fastify + настраиваем logger

const { initDatabase, cleanExpiredSessions, cleanInactiveSessions } = require('./database.js'); //добавляем сюда функции из файла базыданных
const databaseFunc = require('./database.js');

const GameManager = require('./game/GameManager.js');

const path = require('path');
const jwt = require('jsonwebtoken');

//initDatabase();

const gameManager = new GameManager(databaseFunc);

fastify.register(require('@fastify/cors'), { //добавили модуль корс
	origin: ['https://localhost', 'https://localhost:443', 'https://localhost:8443', 'https://localhost:3000'],
	credentials: true
});

fastify.register(require('@fastify/cookie')); // добавили модуль cookie .Для более простой работы с ними .setCookie

fastify.register(require('@fastify/static'), {
	root: path.join('/app/data', 'uploads'),
	prefix: '/uploads/',
	decorateReply: false
});

fastify.register(require('@fastify/multipart'),{ //Pour pouvoir telecharger les avatars
	limits: {
		fileSize: 5 * 1024 * 1024,
		files: 1
	}
});

fastify.register(require('@fastify/websocket'));

fastify.register(require('fastify-socket.io'), {
	path: "/api/socket.io",
	cors: {
		origin: [ 'https://localhost:8443' ],
		methods: ["GET", "POST"],
		credentials: true
	}
});

const userRoutes = require('./routes/users.js'); // Добавялем функционал профилей
const tournamentRoutes = require('./routes/tournament.js');
const websocketRoutes = require('./routes/websocket.js');
const { chatRoutes } = require('./routes/chat.js');

fastify.register(userRoutes);
fastify.register(tournamentRoutes);
fastify.register(chatRoutes);
fastify.register(websocketRoutes, {gameManager});

// fastify.ready -> Function called when all the plugins have been loaded
fastify.ready(err => {
	if (err) throw err;

	// io.use -> Middleware: Runs before making the connection
	// We check the user token to authentificate him
	fastify.io.use((socket, next) => {
		const cookieHeader = socket.handshake.headers.cookie;

		console.log("--- New Socket Connection Attempt ---");
		console.log("Origin:", socket.handshake.headers.origin);
		console.log("Cookies Received:", cookieHeader ? "YES" : "NO");


		if (!cookieHeader) {
			return next(new Error('Auth error: No cookie'));
		}

		const cookies = fastify.parseCookie(cookieHeader);
		const token = cookies['token'];
		if (!token) {
			return next(new Error('Auth error: No token'));
		}

		try {
			const decoded = jwt.verify(token, process.env.JWT_SECRET);
			socket.user = decoded;
			next();
		} catch (error) {
			next(new Error('Auth error: Invalid token'));
		}
	});

	// (socket) io.on -> Event Listener
	// in this case this gets executed on every new connection
	fastify.io.on('connection', (socket) => {
		const userId = socket.user.userId;
		const roomName = `user_${userId}`;
		socket.join(roomName);
		fastify.log.info(`User ${userId} connected to socket room ${roomName}`);

		socket.on('game_decline', (data) => {
			// Forward the message to the Inviter
			fastify.io.to(`user_${data.inviterId}`).emit('game_declined', {
				declinerId: userId
			});
		});
	});
});

setInterval(() => { //Clear sessions ever 1h
	cleanExpiredSessions();
	fastify.log.info('Cleaned expired sessions');
}, 60 * 60 * 1000);

setInterval(() => { // drop stale sessions by inactivity
	cleanInactiveSessions();
	fastify.log.info('Cleaned inactive sessions');
}, 60 * 1000);

fastify.get('/api/health', async (request, reply) => { //http://localhost:3000/api/health
	return {
		status: 'ok',
		message: 'Global service is runnig',
		env: process.env.NODE_ENV
	};
});

const start = async () => {
	try {
		await fastify.listen({ port: 3002, host:'0.0.0.0'}); //Активируем циклы событий
		fastify.log.info('Global service is running');
	} catch (err) {
		fastify.log.error(err);
		process.exit(1);
	}
};

start();
