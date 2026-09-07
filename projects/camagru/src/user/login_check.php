<?php

require_once __DIR__  . '/../data/database.php'; //recuperer PDO

$username = trim($_POST['username'] ?? '');
$password = trim($_POST['password'] ?? '');

$error = [];

//Verification de username 
if ($username === '') {
	$error[] = "Le nom d'utilisateur est obligatoire!";
}

if ($password === '')
{
	$error[] = "Le mot de passe est obligatoire!";
}

if (!empty($error))
{
	foreach ($error as $erro) {
		echo htmlspecialchars($erro) . '<br>';
	}
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

if (!$user) {
	echo "Nom d'utilisateur ou mot de passe incorrect!";
	exit;
}

if (!password_verify($password, $user['password']))
{
	echo "Nom d'utilisateur ou mot de passe incorrect!";
	exit;
}

if(!$user['email_check'])
{
	echo "Vous devez confirmer votre email avant de vous connecter!";
	exit;
}

session_regenerate_id(true);

$_SESSION['user_id'] = $user['id'];
$_SESSION['username'] = $user['username'];

header('Location: /');
exit;