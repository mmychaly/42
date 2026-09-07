<?php

require_once __DIR__  . '/../data/database.php';

$token = $_GET['token'] ?? '';

if ($token === '') {
	echo 'Token de verification est absent!';
	exit;
}

$tokenHash = hash('sha256', $token);

$stmt = $pdo->prepare(
	'SELECT id, email_check, token_verif_expir_at
	FROM users
	WHERE token_verif = :token_verif'
);

$stmt->execute([
	'token_verif' => $tokenHash
]);

$user = $stmt->fetch();

if (!$user) {
	echo 'Token de vérification invalide.';
	exit;
}

if (strtotime($user['token_verif_expir_at']) < time())
{
	echo 'Le lien de verification a expiré!';
	exit;
}

$stmt = $pdo->prepare(
	'UPDATE users
	SET email_check = TRUE,
		token_verif = NULL,
		token_verif_expir_at = NULL
	WHERE id = :id'
);

$stmt->execute([
	'id' => $user['id']
]);

header('Location: /login?verified=1');
exit;