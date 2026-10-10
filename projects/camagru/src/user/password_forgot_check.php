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

// Search for the user associated with this email address.
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

// Create a random password-reset token.
$resetToken = bin2hex(random_bytes(32));

// Hash the token before storing it in the database.
$resetTokenHash = hash('sha256', $resetToken);

// Build the reset link using the original token.
$appUrl = rtrim(getenv('APP_URL'), '/');
$resetLink = $appUrl . '/password-reset?token=' . urlencode($resetToken);


// Store the reset token with a one-hour expiration.
// Use a transaction so the token is kept only if the email is sent successfully.
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
}


$_SESSION['forgot_success'] = "Si il y a un compte associé à cette adresse, un email de réinitialisation sera envoyé!";

header('Location: /password-forgot', true, 303);
exit;
