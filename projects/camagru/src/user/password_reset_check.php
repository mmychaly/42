<?php

require_once __DIR__  . '/../data/database.php';


$token = $_POST['token'] ?? ''; //Reset link
$password = $_POST['password'] ?? '';//New password

// Check that the reset token has the expected format.
if (!is_string($token) || strlen($token) !== 64 || !ctype_xdigit($token))
{
	header('Location: /password-reset', true, 303);
	exit;
}


// Check that the password has the expected type.
if (!is_string($password))
{
	$_SESSION['reset_errors'] = ['Mot de passe invalide'];
	header('Location: /password-reset?token=' . urlencode($token), true, 303);
	exit;
}

$error = [];
// Check that the password meets the required format.
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

// If the password is not valid, store the errors and redirect
// to the reset page to display them.
if (!empty($error))
{
	$_SESSION['reset_errors'] = $error;
	header('Location: /password-reset?token=' . urlencode($token), true, 303);
	exit;
}

// Hash the reset token to compare it with the stored hash
$tokenHash = hash('sha256', $token);

// Hash the new password before storing it in the database.
$passwordHash = password_hash($password, PASSWORD_DEFAULT);

// If the token exists and has not expired,
// update the password and clear the reset token.
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

// If no row was updated, the reset token is invalid or expired.
if ($stmt->rowCount() !== 1)
{
	header('Location: /password-reset', true, 303);
	exit;
}

// If successful, redirect to the login page.
header('Location: /login?password-reset=1', true, 303);
exit;