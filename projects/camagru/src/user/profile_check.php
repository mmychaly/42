<?php

require_once __DIR__  . '/../data/database.php';
require_once __DIR__  . '/../common/mail.php';

$username = trim($_POST['username'] ?? '');
$email = trim($_POST['email'] ?? '');
$emailNotif = isset($_POST['email_notif']) ? 1 : 0;

$error = [];

$stmt = $pdo->prepare(
	'SELECT username, email, email_notif
	FROM users
	WHERE id = :id'
);

$stmt->execute([
	'id' => $_SESSION['user_id']
]);

$currentUser = $stmt->fetch();

if (!$currentUser) {
	echo 'Utilisateur introuvable';
	exit;
}

$usernameChanged = $username !== $currentUser['username'];
$emailChanged = $email !== $currentUser['email'];
$emailNotifChanged = $emailNotif !== $currentUser['email_notif'];

if (!$usernameChanged && !$emailChanged && !$emailNotifChanged)
{
	header('Location: /profile');
	exit;
}

if ($usernameChanged) {
	if ($username === '') //Verification de username 
	{
		$error[] = "Le nom d'utilisateur est obligatoire!";
	} elseif(strlen($username) < 3 || strlen($username) > 50)
	{
		$error[] = "Le nom d'utilisateur min 3 symboles et max 50 symboles";
	} elseif(!preg_match('/^[a-zA-Z0-9_]+$/', $username)) {
		$error[] = "Le nom d'utilisateur doit contenir que des lettres, chiffres et underscore.";
	}
}

if ($emailChanged) {
	if ($email === '')
	{
		$error[] = "Email est obligatoire!";
	} elseif (!filter_var($email, FILTER_VALIDATE_EMAIL))
	{
		$error[] = "Email n'est pas valide!";
	}
}

if($usernameChanged && empty($error)) {
	$stmt = $pdo->prepare(
		'SELECT id
		FROM users
		WHERE username = :username
		AND id != :id'
	);

	$stmt->execute([
		'username' => $username,
		'id' => $_SESSION['user_id']
	]);

	if ($stmt->fetch()) {
		$error[] = "Ce nom d'utilisateur est déjà utilisé.";
	}
}

if($emailChanged && empty($error)) {
	$stmt = $pdo->prepare(
		'SELECT id
		FROM users
		WHERE email = :email
		AND id != :id'
	);

	$stmt->execute([
		'email' => $email,
		'id' => $_SESSION['user_id']
	]);

	if ($stmt->fetch()) {
		$error[] = "Ce email est déjà utilisé.";
	}
}

if (!empty($error))
{
	foreach ($error as $erro) {
		echo htmlspecialchars($erro) . '<br>';
	}
	exit;
}

if (!$emailChanged) {
	$stmt = $pdo->prepare(
		'UPDATE users
		SET username = :username,
			email_notif = :email_notif
		WHERE id = :id'
	);

	$stmt->execute([
		'username' => $username,
		'email_notif' => $emailNotif,
		'id' => $_SESSION['user_id']
	]);

	$_SESSION['username'] = $username;

	header('Location: /profile?updated=1');
	exit;
}

//Changment d'email.
$verifToken = bin2hex(random_bytes(32)); //token pour verifier l'email
$verifTokenHash = hash('sha256', $verifToken); //on hash le token

$stmt = $pdo->prepare(
	'UPDATE users
	SET  username = :username,
		email = :email,
		email_notif = :email_notif,
		email_check = FALSE,
		token_verif = :token_verif,
		token_verif_expir_at = DATE_ADD(NOW(), INTERVAL 24 HOUR)
	WHERE id = :id'
);

$stmt->execute([
	'username' => $username,
	'email' => $email,
	'email_notif' => $emailNotif,
	'token_verif' => $verifTokenHash,
	'id' => $_SESSION['user_id']
]);

$appUrl = rtrim(getenv('APP_URL'), '/');


$verifLink = $appUrl . '/verify-email?token=' . urlencode($verifToken);

$emailRes = sendVerifEmail($username, $email, $verifLink);
if (!$emailRes)
{
	echo "Impossible d'envoyer l'email de verification!";
	exit;
}

$_SESSION['username'] = $username;

header('Location: /profile?email-changed=1');
exit;