<?php

require_once __DIR__  . '/../data/database.php';

$token = $_GET['token'] ?? '';

if (!is_string($token) || strlen($token) !== 64 || !ctype_xdigit($token))
{
	if (isset($_SESSION['user_id']))
	{
		$_SESSION['profile_errors'] = ['Lien de vérification invalide ou expiré!'];
		header('Location: /profile', true, 303);
		exit;
	}
	else
	{
		$_SESSION['login_error'] = 'Lien de vérification invalide ou expiré!';
		header('Location: /login', true, 303);
		exit;
	}
}

$tokenHash = hash('sha256', $token);


$stmt = $pdo->prepare(
	'UPDATE users
	SET email_check = TRUE,
		token_verif = NULL,
		token_verif_expir_at = NULL
	WHERE token_verif = :token_verif
	AND token_verif_expir_at > NOW()'
);

$stmt->execute([
	'token_verif' => $tokenHash
]);

if ($stmt->rowCount() !== 1)
{
	if (isset($_SESSION['user_id']))
	{
		$_SESSION['profile_errors'] = ['Lien de vérification invalide ou expiré!'];
		header('Location: /profile', true, 303);
		exit;
	}
	else
	{
		$_SESSION['login_error'] = 'Lien de vérification invalide ou expiré!';
		header('Location: /login', true, 303);
		exit;
	}
}

if (isset($_SESSION['user_id']))
{
	header('Location: /profile?email-verified=1', true, 303);
	exit;
}
else
{
	header('Location: /login?verified=1', true, 303);
	exit;
}
