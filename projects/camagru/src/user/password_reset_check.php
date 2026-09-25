<?php

require_once __DIR__  . '/../data/database.php';


$token = $_POST['token'] ?? ''; //Token de lien de la réinitialisation
$password = $_POST['password'] ?? '';//New password

//Check token if not compliant request without token == linkError
if (!is_string($token) || strlen($token) !== 64 || !ctype_xdigit($token))
{
	header('Location: /password-reset', true, 303);
	exit;
}

//If password != string , add error to variable and launch new request to display error
if (!is_string($password))
{
	$_SESSION['reset_errors'] = ['Mot de passe invalide'];
	header('Location: /password-reset?token=' . urlencode($token), true, 303);
	exit;
}

$error = [];
//Check compliant for password
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

//If password not comlpliant add error to variable and launch new request to display error
if (!empty($error))
{
	$_SESSION['reset_errors'] = $error;
	header('Location: /password-reset?token=' . urlencode($token), true, 303);
	exit;
}

$tokenHash = hash('sha256', $token);//On hash pour avoir meme quedans db
$passwordHash = password_hash($password, PASSWORD_DEFAULT);//We hash new password to stock in db 

//If token exists in db we aset new password in db and put token in NULL
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

//If db not  upload add error to variable and launch new request to display error
if ($stmt->rowCount() !== 1)
{
	header('Location: /password-reset', true, 303);
	exit;
}

//If it's ok, display /login
header('Location: /login?password-reset=1', true, 303);
exit;