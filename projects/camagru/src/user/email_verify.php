<?php

require_once __DIR__  . '/../data/database.php';

$token = $_GET['token'] ?? '';

if (!is_string($token) || strlen($token) !== 64 || !ctype_xdigit($token))
{
	http_response_code(400);
	exit('Token de vérification invalide');
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
	http_response_code(400);
	exit('Lien de vérification invalide ou expiré!');
}

header('Location: /login?verified=1');
exit;