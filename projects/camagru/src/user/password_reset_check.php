<?php

require_once __DIR__  . '/../data/database.php';


$token = $_POST['token'] ?? '';
$password = $_POST['password'] ?? '';

if (!is_string($token) || strlen($token) !== 64 || !ctype_xdigit($token))
{
	http_response_code(400);
	exit('Token de réinitialisation invalide');
}

if (!is_string($password))
{
	http_response_code(400);
	exit('Mot de passe invalide');
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
$passwordHash = password_hash($password, PASSWORD_DEFAULT);

$stmt = $pdo->prepare(
	'UPDATE users 
	SET password = :password,
			token_reset = NULL,
			token_reset_expir_at = NULL
	WHERE token_reset = :token_reset
	AND token_reset_expir_at > NOW()'
);

$stmt->execute([
	'password' => $passwordHash,
	'token_reset' => $tokenHash
]);

if ($stmt->rowCount() !== 1)
{
	http_response_code(400);
	exit('Lien de réinitialisation invalide ou expiré!');
}

header('Location: /login?password-reset=1');
exit;