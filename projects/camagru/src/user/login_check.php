<?php

require_once __DIR__  . '/../data/database.php'; // Load the PDO database connection.

$username = $_POST['username'] ?? '';//Extract username sent by the form
$password = $_POST['password'] ?? '';//Extract password sent by the form

if (!is_string($username) || !is_string($password))
{
	$_SESSION['login_error'] = 'Identifiants invalide.';
	header('Location: /login', true, 303);
	exit;
}

$username = trim($username);

// Check that both fields are filled in.
if ($username === '' || $password === '') {
	$_SESSION['login_error'] = 'Tout les champs sont obligatoires.';
	header('Location: /login', true, 303);
	exit;
}

// Find the user by username using a prepared statement.
$stmt = $pdo->prepare(
	'SELECT id, username, password, email_check
	FROM users
	WHERE username = :username'
);

$stmt->execute([
	'username' => $username
]);

$user = $stmt->fetch();

// Check that the user exists and that the password matches the stored hash.
if (!$user || !password_verify($password, $user['password'])) 
{
	$_SESSION['login_error'] = "Nom d'utilisateur ou mot de passe incorrect!";
	header('Location: /login', true, 303);
	exit;
}

// Refuse login if the email address has not been verified.
if(!$user['email_check'])
{
	$_SESSION['login_error'] = "Vous devez confirmer votre email avant de vous connecter!";
	header('Location: /login', true, 303);
	exit;
}
// Generate a new session ID after login to prevent session fixation.
session_regenerate_id(true);

// Store the authenticated user information in the PHP session.
$_SESSION['user_id'] = $user['id'];
$_SESSION['username'] = $user['username'];

// Redirect the user to the gallery after successful login.
header('Location: /');
exit;