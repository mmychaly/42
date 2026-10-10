<?php

require_once __DIR__  . '/../data/database.php'; // Load the PDO database connection.
require_once __DIR__  . '/../common/mail.php'; // Load the mail/SMTP functions.

$username = trim($_POST['username'] ?? ''); // Extract the username sent by the form.
$email = trim($_POST['email'] ?? ''); // Extract the email sent by the form.
$password = trim($_POST['password'] ?? ''); // Extract the password sent by the form.

$error = [];

if ($username === '') //Check username 
{
	$error[] = "Le nom d'utilisateur est obligatoire!";
} elseif(strlen($username) < 3 || strlen($username) > 50)
{
	$error[] = "Le nom d'utilisateur min 3 symboles et max 50 symboles";
} elseif(!preg_match('/^[a-zA-Z0-9_]+$/', $username)) {
	$error[] = "Le nom d'utilisateur doit contenir que des lettres, chiffres et underscore.";
}

if ($email === '')
{
	$error[] = "Email est obligatoire!";
} elseif (!filter_var($email, FILTER_VALIDATE_EMAIL))
{
	$error[] = "Email n'est pas valide!";
}

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
	$_SESSION['register_errors'] = $error;

	header('Location: /register', true, 303);
	exit;
}

// Delete unconfirmed users whose verification token has expired.
try {
	$stmt = $pdo->prepare(
		'DELETE FROM users
		WHERE email_check = FALSE
		AND email_check_once = FALSE
		AND token_verif_expir_at <= NOW()'
	);

	$stmt->execute();
} catch (PDOException $er)
{
	$_SESSION['register_errors'] = ["Impossible de verifier la disponibilite du comte."];
	header('Location: /register', true, 303);
	exit;
}

// Check whether the username or email already exists in the database.
$res = $pdo->prepare('SELECT id, username, email
						FROM users
						WHERE username = :username
						OR email = :email');

$res->execute(['username' => $username,
				'email' => $email]);

$data = $res->fetch();

// If the username or email already exists, add an error.
if ($data)
{
	if($data['username'] === $username)
		$error[] = "Ce nom d'utilisteur est déja utilisé.";
	if($data['email'] === $email)
		$error[] = "Cet email est déja utilisé.";
}

if (!empty($error))
{
	$_SESSION['register_errors'] = $error;
	header('Location: /register', true, 303);
	exit;
}

$passwordHash = password_hash($password, PASSWORD_DEFAULT); // Hash the password before storing it in the database.
$verifToken = bin2hex(random_bytes(32)); // Create an email verification token.
$verifTokenHash = hash('sha256', $verifToken); // Hash the verification token before storing it in the database.

// Insert the user into the database with the hashed password,
// hashed verification token and token expiration time.
$stmt = $pdo->prepare(
	'INSERT INTO users (
		username,
		password,
		email,
		token_verif,
		token_verif_expir_at
	)
	VALUES (
		:username,
		:password,
		:email,
		:token_verif,
		DATE_ADD(NOW(), INTERVAL 24 HOUR)
	)'
);

$stmt->execute([
	'username' => $username,
	'password' => $passwordHash,
	'email' => $email,
	'token_verif' => $verifTokenHash
]);


$appUrl = rtrim(getenv('APP_URL'), '/'); // Get the application base URL.

$verifLink = $appUrl . '/verify-email?token=' . urlencode($verifToken); // Build the verification URL with the original token.

// Send the verification email.
$emailRes = sendVerifEmail($username, $email, $verifLink);
if (!$emailRes)
{
	$_SESSION['login_error'] = "Vontre compte a été crée, mais l'email de confirmation n'a pas pu etre envoyé!";
	header('Location: /login', true, 303);
	exit;
}

// Redirect to the login page.
header('Location: /login?registered=1');
exit;
