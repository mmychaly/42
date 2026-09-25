<?php

require_once __DIR__  . '/../data/database.php';
require_once __DIR__  . '/../common/mail.php';

$email = $_POST['email'] ?? '';

if (!is_string($email))
{
	$_SESSION['forgot_error'] = 'Email invalide!';
	header('Location: /password-forgot', true, 303);
	exit;
}

$email = trim($email);

if ($email === '' || !filter_var($email, FILTER_VALIDATE_EMAIL))
{
	$_SESSION['forgot_error'] = 'Email invalide!';
	header('Location: /password-forgot', true, 303);
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
	$_SESSION['forgot_success'] = "Si il y a un compte associé à cette adresse, un email de réinitialisation sera envoyé!";
	header('Location: /password-forgot', true, 303);
	exit;
}

$resetToken = bin2hex(random_bytes(32));
$resetTokenHash = hash('sha256', $resetToken);
$appUrl = rtrim(getenv('APP_URL'), '/');
$resetLink = $appUrl . '/password-reset?token=' . urlencode($resetToken);

try {
	$pdo->beginTransaction();
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
	$emailSent = sendResetPasswordEmail($user["username"], $user["email"], $resetLink);

	if ($emailSent)
		$pdo->commit();
	else
		$pdo->rollBack();
}catch (Throwable $e)
{
	if ($pdo->inTransaction())
		$pdo->rollBack();
	error_log('Password reset failed: ' . $e->getMessage());
}


$_SESSION['forgot_success'] = "Si il y a un compte associé à cette adresse, un email de réinitialisation sera envoyé!";

header('Location: /password-forgot', true, 303);
exit;
