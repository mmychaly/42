const jwt = require('jsonwebtoken');
const crypto = require('crypto');
const { checkAuth } = require('../middleware/checkAuth.js');

const{
	getUserByUsername,
	getUserByEmail,
	getUserById,
	createUser,
	verifyPassword,
	createSession,
	getSessionUser,
	deleteSession,
	setUserStatus,
	touchSession,
	getTwofaData,
	setTwofaTempSecret,
	enableTwofa,
	disableTwofa
} = require('../database.js');


const JWT_SECRET = process.env.JWT_SECRET;
const JWT_EXP = process.env.JWT_EXPIRES_IN || '2d';
const TWOFA_ISSUER = process.env.TWOFA_ISSUER || 'transcendence';
const TWOFA_LOGIN_EXP = '5m';

if (!JWT_SECRET) {
	throw new Error('JWT_SECRET not defined');
}

const BASE32_ALPHABET = 'ABCDEFGHIJKLMNOPQRSTUVWXYZ234567';

function base32Encode(input) {
	let bits = 0;
	let value = 0;
	let output = '';

	for (const byte of input) {
		value = (value << 8) | byte;
		bits += 8;

		while (bits >= 5) {
			output += BASE32_ALPHABET[(value >>> (bits - 5)) & 31];
			bits -= 5;
		}
	}

	if (bits > 0) {
		output += BASE32_ALPHABET[(value << (5 - bits)) & 31];
	}

	return output;
}

function base32Decode(input) {
	let bits = 0;
	let value = 0;
	const output = [];

	const cleanedInput = input.toUpperCase().replace(/=+$/g, '').replace(/[^A-Z2-7]/g, '');

	for (const char of cleanedInput) {
		const ind = BASE32_ALPHABET.indexOf(char);

		if (ind === -1) continue;

		value = (value << 5) | ind;
		bits += 5;

		if (bits >= 8) {
			output.push((value >>> (bits - 8)) & 255);
			bits -= 8;
		}
	}

	return Buffer.from(output);
}

function generateTOTP(secret, counter) {
	const key = base32Decode(secret);
	const buffer = Buffer.alloc(8);
	buffer.writeBigUInt64BE(BigInt(counter));

	const hmac = crypto.createHmac('sha1', key).update(buffer).digest();
	const offset = hmac[hmac.length - 1] & 0x0f;
	const binaryCode =
		((hmac[offset] & 0x7f) << 24) |
		((hmac[offset + 1] & 0xff) << 16) |
		((hmac[offset + 2] & 0xff) << 8) |
		(hmac[offset + 3] & 0xff);

	return String(binaryCode % 1000000).padStart(6, '0');
}

function verifyTOTP(secret, code, window = 1) {
	if (!secret) return false;

	const cleanCode = String(code ?? '').replace(/\s+/g, '');
	if (!/^\d{6}$/.test(cleanCode)) return false;

	const timeCounter = Math.floor(Date.now() / 1000 / 30);

	for (let offset = -window; offset <= window; offset++) {
		if (generateTOTP(secret, timeCounter + offset) === cleanCode) {
			return true;
		}
	}

	return false;
}

function buildOtpauthUrl(secret, username) {
	const label = encodeURIComponent(`${TWOFA_ISSUER}:${username}`);
	const issuer = encodeURIComponent(TWOFA_ISSUER);

	return `otpauth://totp/${label}?secret=${secret}&issuer=${issuer}&algorithm=SHA1&digits=6&period=30`;
}

module.exports = async function authRoutes(fastify, options) {
	fastify.post('/api/auth/register', async (request, reply) => {
		const {username, email, password} = request.body;

		if(!username || !email || !password) {
			reply.code(400);
			return {message: 'Username , email and password required'};
		}
		
		if (username.length < 2) {
			reply.code(400);
			return { message: 'Username must be least 2 characters'};
		}

		if (password.length < 4) {
			reply.code(400);
			return { message: 'Password must be least 4 characters'};
		}

		try {
			const existUser = getUserByUsername(username);
			if (existUser) 
			{
				reply.code(409);
				return { message: 'Username already exists'};
			}

			const existEmail = getUserByEmail(email);
			if (existEmail)
			{
				reply.code(409);
				return { message: 'Email already exists'};
			}

			const newUser = createUser(username, email, password);
			const sessionId = createSession(newUser.id);

			const token = jwt.sign(
				{
					userId: newUser.id,
					username: newUser.username,
					sessionId: sessionId
				},
				JWT_SECRET,
				{ expiresIn: JWT_EXP}
			);

			reply.setCookie('token', token, {
				httpOnly: true,
				sameSite: 'strict',
				maxAge: 2 * 24 * 60 * 60,
				path: '/'
			});

			return {
				user: {
					id: newUser.id,
					username: newUser.username,
					displayName: newUser.display_name,
					status: 'online',
					avatarUrl: newUser.avatar_url,
					statusMessage: newUser.status_message,
					twofaEnabled: newUser.twofa_enabled
				}
			};
		} catch (error) {
			fastify.log.error(error);
			reply.code(500);
			return { message: 'Filed to register user'};
		}
	});

	fastify.post('/api/auth/login', async (request, reply) => {
		const { login, password } = request.body;
		if (!login || ! password) 
		{
			reply.code(400);
			return { message: 'Login and password are required'};
		}

		try {
			let user = getUserByUsername(login);
			if (!user) {
				user = getUserByEmail(login);
			}

			if (!user)
			{
				reply.code(401);
				return { message: 'Invalid login'};
			}

			if (!verifyPassword(user, password)) {
				reply.code(401);
				return {message: "Wrong password"};
			}

			if (user.twofa_enabled) {
				if (!user.twofa_secret) {
					reply.code(409);
					return { message: '2FA is not configured' };
				}
				const tempToken = jwt.sign(
					{
						userId: user.id,
						purpose: '2fa'
					},
					JWT_SECRET,
					{ expiresIn: TWOFA_LOGIN_EXP }
				);

				return {
					requires2fa: true,
					tempToken
				};
			}

			const sessionId = createSession(user.id);

			const token = jwt.sign(
				{
					userId: user.id,
					username: user.username,
					sessionId: sessionId
				},
				JWT_SECRET,
				{expiresIn: JWT_EXP}
			);

			reply.setCookie('token', token, {
				httpOnly: true,
				sameSite: 'strict',
				maxAge: 2 * 24 * 60 * 60,
				path: '/'
			});

			return {
				user: {
					id: user.id,
					username: user.username,
					displayName: user.display_name,
					avatarUrl: user.avatar_url,
					status: 'online',
					statusMessage: user.status_message,
					twofaEnabled: user.twofa_enabled
				}
			};
		} catch (error) {
			fastify.log.error(error);
			reply.code(500);
			return { message: 'Login failed'};
		}
	});

	fastify.post('/api/auth/2fa', async (request, reply) => {
		const { tempToken, code } = request.body;
		if (!tempToken || !code) {
			reply.code(400);
			return { message: 'Temporary token and code are required' };
		}

		try {
			const decoded = jwt.verify(tempToken, JWT_SECRET);
			if (!decoded || decoded.purpose !== '2fa' || !decoded.userId) {
				reply.code(401);
				return { message: 'Invalid 2FA token' };
			}

			const user = getUserById(decoded.userId);
			const twofa = getTwofaData(decoded.userId);
			if (!user || !twofa || !twofa.twofa_enabled || !twofa.twofa_secret) {
				reply.code(401);
				return { message: '2FA is not enabled for this user' };
			}

			if (!verifyTOTP(twofa.twofa_secret, code)) {
				reply.code(401);
				return { message: 'Invalid 2FA code' };
			}

			const sessionId = createSession(user.id);
			const token = jwt.sign(
				{
					userId: user.id,
					username: user.username,
					sessionId: sessionId
				},
				JWT_SECRET,
				{ expiresIn: JWT_EXP }
			);

			reply.setCookie('token', token, {
				httpOnly: true,
				sameSite: 'strict',
				maxAge: 2 * 24 * 60 * 60,
				path: '/'
			});

			return {
				user: {
					id: user.id,
					username: user.username,
					displayName: user.display_name,
					avatarUrl: user.avatar_url,
					status: 'online',
					statusMessage: user.status_message,
					twofaEnabled: user.twofa_enabled
				}
			};
		} catch (error) {
			if (error.name === 'TokenExpiredError') {
				reply.code(401);
				return { message: '2FA token expired' };
			}
			if (error.name === 'JsonWebTokenError') {
				reply.code(401);
				return { message: 'Invalid 2FA token' };
			}
			fastify.log.error(error);
			reply.code(500);
			return { message: '2FA verification failed' };
		}
	});

	fastify.get('/api/2fa/setup', { preHandler: checkAuth }, async (request, reply) => {
		const data = getTwofaData(request.user.id);
		if (data && data.twofa_enabled) {
			reply.code(409);
			return { message: '2FA already enabled' };
		}

		const secret = base32Encode(crypto.randomBytes(20));
		setTwofaTempSecret(request.user.id, secret);

		const otpauthUrl = buildOtpauthUrl(secret, request.user.username);
		return {
			otpauthUrl,
			manualEntryKey: secret
		};
	});

	fastify.post('/api/2fa/verify', { preHandler: checkAuth }, async (request, reply) => {
		const { code } = request.body;
		if (!code) {
			reply.code(400);
			return { message: '2FA code is required' };
		}

		const data = getTwofaData(request.user.id);
		if (!data || !data.twofa_temp_secret) {
			reply.code(400);
			return { message: 'No pending 2FA setup found' };
		}

		const ok = verifyTOTP(data.twofa_temp_secret, code);
		if (!ok) {
			reply.code(401);
			return { message: 'Invalid 2FA code' };
		}

		enableTwofa(request.user.id, data.twofa_temp_secret);
		return { enabled: true };
	});

	fastify.post('/api/2fa/disable', { preHandler: checkAuth }, async (request, reply) => {
		const { code } = request.body;
		if (!code) {
			reply.code(400);
			return { message: '2FA code is required' };
		}

		const data = getTwofaData(request.user.id);
		if (!data || !data.twofa_enabled || !data.twofa_secret) {
			reply.code(400);
			return { message: '2FA is not enabled' };
		}

		const ok = verifyTOTP(data.twofa_secret, code);
		if (!ok) {
			reply.code(401);
			return { message: 'Invalid 2FA code' };
		}

		disableTwofa(request.user.id);
		return { enabled: false };
	});

	fastify.post('/api/auth/logout', { preHandler: checkAuth }, async (request, reply) => {
		deleteSession(request.user.sessionId);

		reply.clearCookie('token', {path: '/'});
		reply.code(204).send();
	});

	fastify.post('/api/presence/ping', { preHandler: checkAuth }, async (request, reply) => {
		touchSession(request.user.sessionId);
		setUserStatus(request.user.id, 'online');
		reply.code(204).send();
	});

	fastify.get('/api/auth/me', {preHandler: checkAuth}, async (request, reply) => {
		return {
			user: {
				id: request.user.id,
				username: request.user.username,
				displayName: request.user.displayName,
				status: request.user.status,
				statusMessage: request.user.statusMessage,
				avatarUrl: request.user.avatarUrl,
				twofaEnabled: request.user.twofaEnabled
			}
		};
	});
}
