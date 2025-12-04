// backend/src/routes/auth.js

// ✅ Pas besoin de require('dotenv') ici, déjà chargé dans index.js

const jwt = require('jsonwebtoken');
const {
  getUserByUsername,
  getUserByEmail,
  createUser,
  verifyPassword,
  createSession,
  getSessionUser,
  deleteSession
} = require('../database');

// ✅ Utilise les variables d'environnement
const JWT_SECRET = process.env.JWT_SECRET;
const JWT_EXPIRES_IN = process.env.JWT_EXPIRES_IN || '7d';

// ⚠️ Validation : vérifie que JWT_SECRET existe
if (!JWT_SECRET) {
  throw new Error('JWT_SECRET is not defined in environment variables');
}

async function authRoutes(fastify, options) {
  
  // POST /api/auth/register
  fastify.post('/api/auth/register', async (request, reply) => {
    const { username, email, password } = request.body;
    
    if (!username || !email || !password) {
      reply.code(400);
      return { message: 'Username, email and password are required' };
    }
    
    if (username.length < 3) {
      reply.code(400);
      return { message: 'Username must be at least 3 characters' };
    }
    
    if (password.length < 6) {
      reply.code(400);
      return { message: 'Password must be at least 6 characters' };
    }
    
    try {
      const existingUser = getUserByUsername(username);
      if (existingUser) {
        reply.code(409);
        return { message: 'Username already exists' };
      }
      
      const existingEmail = getUserByEmail(email);
      if (existingEmail) {
        reply.code(409);
        return { message: 'Email already exists' };
      }
      
      const newUser = createUser(username, email, password);
      const sessionId = createSession(newUser.id);
      
      // ✅ Utilise JWT_SECRET depuis .env
      const token = jwt.sign(
        { 
          userId: newUser.id, 
          username: newUser.username,
          sessionId: sessionId
        },
        JWT_SECRET,
        { expiresIn: JWT_EXPIRES_IN }
      );
      
      reply.setCookie('token', token, {
        httpOnly: true,
        secure: process.env.NODE_ENV === 'production',  // ✅ Secure seulement en production
        sameSite: 'strict',
        maxAge: 7 * 24 * 60 * 60,
        path: '/'
      });
      
      return {
        user: {
          id: newUser.id,
          username: newUser.username,
          displayName: newUser.display_name,
          status: 'online'
        }
      };
      
    } catch (error) {
      fastify.log.error(error);
      reply.code(500);
      return { message: 'Failed to register user' };
    }
  });
  
  // POST /api/auth/login
  fastify.post('/api/auth/login', async (request, reply) => {
    const { login, password } = request.body;
    
    if (!login || !password) {
      reply.code(400);
      return { message: 'Login and password are required' };
    }
    
    try {
      let user = getUserByUsername(login);
      if (!user) {
        user = getUserByEmail(login);
      }
      
      if (!user) {
        reply.code(401);
        return { message: 'Invalid credentials' };
      }
      
      if (!verifyPassword(user, password)) {
        reply.code(401);
        return { message: 'Invalid credentials' };
      }
      
      const sessionId = createSession(user.id);
      
      // ✅ Utilise JWT_SECRET depuis .env
      const token = jwt.sign(
        { 
          userId: user.id, 
          username: user.username,
          sessionId: sessionId
        },
        JWT_SECRET,
        { expiresIn: JWT_EXPIRES_IN }
      );
      
      reply.setCookie('token', token, {
        httpOnly: true,
        secure: process.env.NODE_ENV === 'production',
        sameSite: 'strict',
        maxAge: 7 * 24 * 60 * 60,
        path: '/'
      });
      
      return {
        user: {
          id: user.id,
          username: user.username,
          displayName: user.display_name,
          status: 'online'
        }
      };
      
    } catch (error) {
      fastify.log.error(error);
      reply.code(500);
      return { message: 'Login failed' };
    }
  });
  
  // POST /api/auth/logout
  fastify.post('/api/auth/logout', async (request, reply) => {
    const token = request.cookies.token;
    
    if (token) {
      try {
        const decoded = jwt.verify(token, JWT_SECRET);
        deleteSession(decoded.sessionId);
      } catch (error) {
        // Token invalide, ignore
      }
    }
    
    reply.clearCookie('token', { path: '/' });
    return { success: true };
  });
  
  // GET /api/auth/me
  fastify.get('/api/auth/me', async (request, reply) => {
    const token = request.cookies.token;
    
    if (!token) {
      reply.code(401);
      return { message: 'Not authenticated' };
    }
    
    try {
      // ✅ Utilise JWT_SECRET depuis .env
      const decoded = jwt.verify(token, JWT_SECRET);
      const user = getSessionUser(decoded.sessionId);
      
      if (!user) {
        reply.code(401);
        return { message: 'Session expired or invalid' };
      }
      
      return {
        user: {
          id: user.id,
          username: user.username,
          displayName: user.displayName,
          status: user.status
        }
      };
      
    } catch (error) {
      if (error.name === 'JsonWebTokenError') {
        reply.code(401);
        return { message: 'Invalid token' };
      }
      if (error.name === 'TokenExpiredError') {
        reply.code(401);
        return { message: 'Token expired' };
      }
      fastify.log.error(error);
      reply.code(500);
      return { message: 'Failed to fetch user' };
    }
  });
}

module.exports = authRoutes;