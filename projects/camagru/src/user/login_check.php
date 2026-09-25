<?php

require_once __DIR__  . '/../data/database.php'; //recuperer PDO

$username = $_POST['username'] ?? '';
$password = $_POST['password'] ?? '';

if (!is_string($username) || !is_string($password))
{
	$_SESSION['login_error'] = 'Identifiants invalide.';
	header('Location: /login', true, 303);
	exit;
}

$username = trim($username);

//Verification de username 
if ($username === '' || $password === '') {
	$_SESSION['login_error'] = 'Tout les champs sont obligatoires.';
	header('Location: /login', true, 303);
	exit;
}

$stmt = $pdo->prepare(
	'SELECT id, username, password, email_check
	FROM users
	WHERE username = :username'
);

$stmt->execute([
	'username' => $username
]);

$user = $stmt->fetch();

if (!$user || !password_verify($password, $user['password'])) 
{
	$_SESSION['login_error'] = "Nom d'utilisateur ou mot de passe incorrect!";
	header('Location: /login', true, 303);
	exit;
}


if(!$user['email_check'])
{
	$_SESSION['login_error'] = "Vous devez confirmer votre email avant de vous connecter!";
	header('Location: /login', true, 303);
	exit;
}

session_regenerate_id(true);

$_SESSION['user_id'] = $user['id'];
$_SESSION['username'] = $user['username'];

header('Location: /');
exit;