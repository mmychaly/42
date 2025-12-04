// backend/src/database.js
const Database = require('better-sqlite3');
const crypto = require('crypto');
const path = require('path');

const dbPath = path.join('/app/data', 'database.db');
const db = new Database(dbPath);

// Hash password avec SHA256 (simple pour le projet)
function hashPassword(password) {
  return crypto.createHash('sha256').update(password).digest('hex');
}

// Initialisation de la base de données
function initDatabase() {
  db.exec(`
    CREATE TABLE IF NOT EXISTS users (
      id TEXT PRIMARY KEY,
      username TEXT UNIQUE NOT NULL,
      email TEXT UNIQUE NOT NULL,
      password TEXT NOT NULL,
      display_name TEXT NOT NULL,
      created_at DATETIME DEFAULT CURRENT_TIMESTAMP
    )
  `);

  db.exec(`
    CREATE TABLE IF NOT EXISTS sessions (
      session_id TEXT PRIMARY KEY,
      user_id TEXT NOT NULL,
      created_at DATETIME DEFAULT CURRENT_TIMESTAMP,
      expires_at DATETIME NOT NULL,
      FOREIGN KEY (user_id) REFERENCES users(id) ON DELETE CASCADE
    )
  `);
}

// ========== Fonctions User ==========

function getAllUsers() {
  return db.prepare('SELECT id, username, email, display_name, created_at FROM users').all();
}

function getUserById(id) {
  return db.prepare('SELECT id, username, email, display_name, created_at FROM users WHERE id = ?').get(id);
}

function getUserByUsername(username) {
  return db.prepare('SELECT * FROM users WHERE username = ?').get(username);
}

function getUserByEmail(email) {
  return db.prepare('SELECT * FROM users WHERE email = ?').get(email);
}

function createUser(username, email, password) {
  const id = crypto.randomUUID();
  const passwordHash = hashPassword(password);
  const displayName = username; // Par défaut, display_name = username
  
  const stmt = db.prepare(`
    INSERT INTO users (id, username, email, password, display_name) 
    VALUES (?, ?, ?, ?, ?)
  `);
  
  stmt.run(id, username, email, passwordHash, displayName);
  
  return getUserById(id);
}

function deleteUser(id) {
  return db.prepare('DELETE FROM users WHERE id = ?').run(id);
}

function verifyPassword(user, password) {
  return user.password === hashPassword(password);
}

// ========== Fonctions Session ==========

function createSession(userId) {
  const sessionId = crypto.randomUUID();
  const expiresAt = new Date(Date.now() + 7 * 24 * 60 * 60 * 1000); // 7 jours
  
  const stmt = db.prepare(`
    INSERT INTO sessions (session_id, user_id, expires_at) 
    VALUES (?, ?, ?)
  `);
  
  stmt.run(sessionId, userId, expiresAt.toISOString());
  
  return sessionId;
}

function getSessionUser(sessionId) {
  const stmt = db.prepare(`
    SELECT u.id, u.username, u.display_name
    FROM sessions s
    JOIN users u ON s.user_id = u.id
    WHERE s.session_id = ? AND s.expires_at > datetime('now')
  `);
  
  return stmt.get(sessionId);
}

function deleteSession(sessionId) {
  return db.prepare('DELETE FROM sessions WHERE session_id = ?').run(sessionId);
}

function cleanExpiredSessions() {
  return db.prepare('DELETE FROM sessions WHERE expires_at < datetime("now")').run();
}

module.exports = {
  initDatabase,
  getAllUsers,
  getUserById,
  getUserByUsername,
  getUserByEmail,
  createUser,
  deleteUser,
  verifyPassword,
  createSession,
  getSessionUser,
  deleteSession,
  cleanExpiredSessions
};