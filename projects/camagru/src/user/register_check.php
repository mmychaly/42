<?php

require_once __DIR__  . '/../data/database.php'; //recuperer pdo, connection avec db
require_once __DIR__  . '/../common/mail.php'; //recuper envirenement de SMTP
//
$username = trim($_POST['username'] ?? '');
$email = trim($_POST['email'] ?? '');
$password = trim($_POST['password'] ?? '');


$error = [];

if ($username === '') //Verification de username 
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
	foreach ($error as $erro) {
		echo htmlspecialchars($erro) . '<br>';
	}
	exit;
}

$res = $pdo->prepare('SELECT id, username, email
						FROM users
						WHERE username = :username
						OR email = :email');

$res->execute(['username' => $username,
				'email' => $email]);

$data = $res->fetch();

if ($data)
{
	if($data['username'] === $username)
		$error[] = "Ce nom d'utilisteur est déja utilisé.";
	if($data['email'] === $email)
		$error[] = "Cet email est déja utilisé.";
}

if (!empty($error))
{
	foreach ($error as $erro) {
		echo htmlspecialchars($erro) . '<br>';
	}
	exit;
}

$passwordHash = password_hash($password, PASSWORD_DEFAULT); // on transforme le mot de pass vers les symboles aleatoire
$verifToken = bin2hex(random_bytes(32)); //token pour verifier l'email
$verifTokenHash = hash('sha256', $verifToken); //on hash le token

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

$appUrl = rtrim(getenv('APP_URL'), '/');


$verifLink = $appUrl . '/verify-email?token=' . urlencode($verifToken);

$emailRes = sendVerifEmail($username, $email, $verifLink);
if (!$emailRes)
{
	echo "Impossible d'envoyer l'email de verification!";
	exit;
}

header('Location: /login?registered=1');
exit;
