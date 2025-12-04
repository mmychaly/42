const jwt = require('jsonwebtoken');

const{
	getUserByUsername,
	getUserByEmail,
	createUser,
	verifyPassword,
	createSession,
	getSessionUser,
	deleteSession
} = require('../database.js');

const JWT_SECRET = process.env.JWT_SECRET;
const JWT_EXP = process.env.JWT_EXPIRES_IN || '7d';

if (!JWT_SECRET) {
	throw new Error('JWT_SECRET not defined');
}


async function authRoutes(fastify, options) {
	fastify.post('/api/auth/register', async (request, reply) => {
		const {username, email, password} = request.body;

		if(!username || !email || !password) {
			reply.code(400);
			return {message: 'Username , email and password required'};
		}
		
	});
}