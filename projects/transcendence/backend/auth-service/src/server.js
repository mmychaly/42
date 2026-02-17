require('dotenv').config(); //Добавляем доступ к .env

const fastify = require('fastify')({ logger: true }); //Создаем сервер добавив модуль fastify + настраиваем logger

const { initDatabase } = require('./database.js');

fastify.register(require('@fastify/cors'), { //добавили модуль корс
	origin: ['https://localhost', 'https://localhost:443', 'https://localhost:8443'],
	credentials: true
});

fastify.register(require('@fastify/cookie'));

initDatabase();

fastify.register(require('./routes/auth.js')); //Добавляем функционал аунтификации

const start = async () => {
	try {
		await fastify.listen({ port: 3001, host:'0.0.0.0'});
		fastify.log.info('Server Auth is running');
	} catch (err) {
		fastify.log.error(err);
		process.exit(1);
	}
};

start();
