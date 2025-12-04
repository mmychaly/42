// backend/src/middleware/auth.js

const jwt = require('jsonwebtoken');
const { getSessionUser } = require('../database');

// ✅ Utilise JWT_SECRET depuis .env
const JWT_SECRET = process.env.JWT_SECRET;

if (!JWT_SECRET) {
  throw new Error('JWT_SECRET is not defined in environment variables');
}

async function requireAuth(request, reply) {
  const token = request.cookies.token;
  
  if (!token) {
    reply.code(401);
    throw new Error('Authentication required');
  }
  
  try {
    // ✅ Utilise JWT_SECRET depuis .env
    const decoded = jwt.verify(token, JWT_SECRET);
    const user = getSessionUser(decoded.sessionId);
    
    if (!user) {
      reply.code(401);
      throw new Error('Session expired or invalid');
    }
    
    request.user = user;
    
  } catch (error) {
    if (error.name === 'JsonWebTokenError') {
      reply.code(401);
      throw new Error('Invalid token');
    }
    if (error.name === 'TokenExpiredError') {
      reply.code(401);
      throw new Error('Token expired');
    }
    throw error;
  }
}

module.exports = { requireAuth };