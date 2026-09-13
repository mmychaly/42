<?php

require_once __DIR__  . '/../data/database.php';


$token = $_POST['token'] ?? '';
$password = $_POST['password'] ?? '';

if ($token === '') {
	echo 'Token de réinitialisation absent!';
	exit;
}

$error = [];

if ($password === '')
{
	$error[] = "Le mot de passe est obligatoire!";
} elseif (strlen($password) < 8) 
{
	$error[] = "Le mot de passe doit contenir minimum 8 symboles!";
}elseif (!preg_match('/[a-z]/', $password)) 
{
	$error[] = "Le mot de passe doit contenir au moins une lettre en minuscule!";
} elseif (!preg_match('/[A-Z]/', $password)) 
{
	$error[] = "Le mot de passe doit contenir au moins une lettre en majuscule!";
} elseif (!preg_match('/[0-9]/', $password)) 
{
	$error[] = "Le mot de passe doit contenir au moins un chiffre!";
}

if (!empty($error))
{
	foreach ($error as $erro) {
		echo htmlspecialchars($erro) . '<br>';
	}
	exit;
}

$tokenHash = hash('sha256', $token);

$stmt = $pdo->prepare(
	'SELECT id, token_reset_expir_at
	FROM users
	WHERE token_reset = :token_reset'
);

$stmt->execute([
	'token_reset' => $tokenHash
]);

$user = $stmt->fetch();

if (!$user) {
	echo 'Lien de réinitialisation invalide.';
	exit;
}

if (strtotime($user['token_reset_expir_at']) < time())
{
	echo 'Le lien de réinitialisation a expiré!';
	exit;
}

$passwordHash = password_hash($password, PASSWORD_DEFAULT);

$stmt = $pdo->prepare(
	'UPDATE users 
	SET password = :password,
			token_reset = NULL,
			token_reset_expir_at = NULL
	WHERE id = :id'
);

$stmt->execute([
	'password' => $passwordHash,
	'id' => $user["id"]
]);

header('Location: /login?password-reset=1');
exit;