const Database = require('better-sqlite3'); //Здесь Database я вляется ссылкой на класс переданный через модуль
const crypto = require('crypto');
const { exists } = require('fs');
const path = require('path');

const dbPath = path.join('/app/data', 'database.db'); //Сохраняем путь к базе данных
const db = new Database(dbPath); // через ссылку на класс создаем обект данного класса

function hashPassword(password) {
	return crypto.createHash('sha256').update(password).digest('hex');
}

db.pragma('foreign_keys = ON');

//status в users? 
function initDatabase() {
	

	db.exec(`
		CREATE TABLE IF NOT EXISTS users (
		id TEXT PRIMARY KEY,
		username TEXT UNIQUE NOT NULL,
		email TEXT UNIQUE NOT NULL,
		password TEXT NOT NULL,
		status TEXT DEFAULT 'offline',
		created_at DATETIME DEFAULT CURRENT_TIMESTAMP
		)
	`);

	db.exec(`
		CREATE TABLE IF NOT EXISTS sessions (
		sessions_id TEXT PRIMARY KEY,
		user_id TEXT UNIQUE NOT NULL,
		created_at DATETIME DEFAULT CURRENT_TIMESTAMP,
		expires_at DATETIME NOT NULL,
		FOREIGN KEY (user_id) REFERENCES users(id) ON DELETE CASCADE 
		)
	`);
}

function getAllUsers() {
	return db.prepare('SELECT id, username, email, created_at FROM users').all();
}

function getUserById(id) {
	return db.prepare('SELECT id, username, email, created_at FROM users WHERE id = ?').get(id);

}

function getUserByEmail(email) {
	return db.prepare('SELECT * FROM users WHER email = ?').get(email);
}