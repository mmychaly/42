<?php

require_once __DIR__  . '/../data/database.php';
require_once __DIR__  . '/../common/mail.php';

$email = trim($_POST['email'] ?? '');

if ($email === '' || !filter_var($email, FILTER_VALIDATE_EMAIL))
{
	echo "Email invalide";
	exit;
}

$stmt = $pdo->prepare(
	'SELECT id, username, email
	FROM users
	WHERE email = :email'
);

$stmt->execute([
	'email' => $email
]);

$user = $stmt->fetch();

if (!$user)
{
	echo "Ce utilisteur n'a pas trouvé";
	exit;
}

$resetToken = bin2hex(random_bytes(32));
$resetTokenHash = hash('sha256', $resetToken);

$stmt = $pdo->prepare(
	'UPDATE users 
		SET token_reset = :token_reset,
			token_reset_expir_at = DATE_ADD(NOW(), INTERVAL 1 HOUR)
	WHERE id = :id'
);

$stmt->execute([
	'token_reset' => $resetTokenHash,
	'id' => $user["id"]
]);

$appUrl = rtrim(getenv('APP_URL'), '/');


$resetLink = $appUrl . '/password-reset?token=' . urlencode($resetToken);

$emailSent = sendResetPasswordEmail($user["username"], $user["email"], $resetLink);

if (!$emailSent)
{
	echo "Impossible d'envoyer l'email de reinitialisation!";
	exit;
}

echo "L'email de reinitialisation a été envoyé.";