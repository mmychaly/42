require('dotenv').config(); //Добавляем доступ к .env

const fastify = require("fastify")({ logger: true }); //Создаем сервер добавив модуль fastify + настраиваем logger
const { initDatabase, cleanExpiredSessions } = require('./database.js'); //добавляем сюда функции из файла базыданных
const authRoutes = require('./routes/auth.js'); //Добавляем функционал аунтификации 
const userRoutes = require('./routes/users.js'); // Добавялем функционал профилей

fastify.register(require('@fastify/cors'), { //добавили модуль корс
	origin: ['https://localhost', 'https://localhost:443'],
	credentials: true
});

fastify.register(require('@fastify/cookie')); // добавили модуль cookie .Для более простой работы с ними .setCookie 

initDatabase();

setInterval(() => { //Clear sessions ever 1h
	cleanExpiredSessions();
	fastify.log.info('Cleaned expired sessions');
}, 60 * 60 * 1000);

fastify.register(authRoutes);
fastify.register(userRoutes);

fastify.get('/api/health', async (request, reply) => { //http://localhost:3000/api/health
	return {
		status: 'ok',
		message: 'Backend is runnig',
		env: process.env.NODE_ENV
	};
});

const start = async () => {
	try {
		const port = process.env.PORT || 3000;
		await fastify.listen({ port, host:'0.0.0.0'}); //Активируем циклы событий 
		fastify.log.info('Server is running');
	} catch (err) {
		fastify.log.error(err);
		process.exit(1);
	}
};

start();