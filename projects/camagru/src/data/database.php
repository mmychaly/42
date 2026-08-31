<?php

$host = getenv('DB_HOST');
$port = getenv('DB_PORT');
$name = getenv('DB_NAME');
$user = getenv('DB_USER');
$password = getenv('DB_PASSWORD');

$dsn = "mysql:host=$host;port=$port;dbname=$name;charset=utf8mb4";

try {
	$pdo = new PDO($dsn, $user, $password, [
		PDO::ATTR_ERRMODE => PDO::ERRMODE_EXCEPTION
	]);
} catch (PDOException $e) {
	die('Database connection error ');
}