const jwt = require('jsonwebtoken');
const { getSessionUser, touchSession } = require('../database.js');

const JWT_SECRET = process.env.JWT_SECRET;

if (!JWT_SECRET)
{
	throw new Error('JWT_Secret not defined in env');
}

function getUserFromToken(token) {
	if (!token) {
		const error = new Error('Authentification required');
		error.statusCode = 401;
		throw error;
	}

	try {
		const decoded = jwt.verify(token, JWT_SECRET);
		const user = getSessionUser(decoded.sessionId);

		if (!user) {
			const error = new Error('Session expired or invalid');
			error.statusCode = 401;
			throw error;
		}

		touchSession(decoded.sessionId);

		return {
			id: user.id,
			username: user.username,
			displayName: user.display_name,
			avatarUrl: user.avatar_url,
			status: user.status,
			statusMessage: user.status_message,
			twofaEnabled: user.twofa_enabled,
			sessionId: decoded.sessionId
		};

	} catch(error) {
		let newError;
		if (error.name === 'JsonWebTokenError') {
			newError = new Error('Invalid token');
		} else if (error.name === 'TokenExpiredError') {
			newError = new Error('Expired token');
		} else if (error.statusCode) {
			throw error;
		} else {
			newError = new Error('An unexpected error occurred during authentication.');
		}
		newError.statusCode = 401;
		throw newError;
	}
}


async function checkAuth(request, reply)
{
	try {
		const user = getUserFromToken(request.cookies.token);
		request.user = user;
	} catch (e) {
		reply.code(e.statusCode || 401);
		throw e;
	}
}

module.exports = {checkAuth, getUserFromToken};
