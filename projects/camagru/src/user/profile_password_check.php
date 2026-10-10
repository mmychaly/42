<?php

//Form from profile to change password

require_once __DIR__  . '/../data/database.php';


$currentPassword = $_POST['current_password'] ?? '';//Extract current password sent by from
$newPassword = $_POST['new_password'] ?? '';//Extract new password sent by from
$confirmPassword = $_POST['confirm_password'] ?? '';//Extract confirm password sent by from

$error = [];

if (!is_string($currentPassword) || !is_string($newPassword) || !is_string($confirmPassword))
{
	$_SESSION['profile_password_errors'] = ['Données invalides!'];
	header('Location: /profile', true, 303);
	exit;
}


if ($currentPassword === '')
{
	$error[] = "Le mot de passe actuel est obligatoire!";
}

//verifying new password
if ($newPassword === '')
{
	$error[] = "Le nouveau mot de passe est obligatoire!";
} elseif (strlen($newPassword) < 8) 
{
	$error[] = "Le mot de passe doit contenir minimum 8 symboles!";
}elseif (!preg_match('/[a-z]/', $newPassword)) 
{
	$error[] = "Le mot de passe doit contenir au moins une lettre en minuscule!";
} elseif (!preg_match('/[A-Z]/', $newPassword)) 
{
	$error[] = "Le mot de passe doit contenir au moins une lettre en majuscule!";
} elseif (!preg_match('/[0-9]/', $newPassword)) 
{
	$error[] = "Le mot de passe doit contenir au moins un chiffre!";
}

if ($newPassword !== $confirmPassword) {
	$error[] = "Le mot de passe de confirmation n'est pas le même.";
}

if (!empty($error))
{
	$_SESSION['profile_password_errors'] = $error;
	header('Location: /profile', true, 303);
	exit;
}

$stmt = $pdo->prepare(
	'SELECT password
	FROM users
	WHERE id = :id'
);

$stmt->execute([
	'id' => $_SESSION['user_id']
]);

$user = $stmt->fetch();

if (!$user) {
	unset($_SESSION['user_id'], $_SESSION['username']);
	$_SESSION['login_error'] = "Votre compte est introuvable.Veuillez vous recconnecter.";
	header('Location: /login', true, 303);
	exit;
}

//verifying if current password is real password
if (!password_verify($currentPassword, $user['password'])) {
	$_SESSION['profile_password_errors'] = ['Le mot de passe actuel est incorrect!'];
	header('Location: /profile', true, 303);
	exit;
}

//verifying new password are different to current password
if (password_verify($newPassword, $user['password'])) {
	$_SESSION['profile_password_errors'] = ['Le nouveau mot de passe doit etre différent du mot de passe actuel!'];
	header('Location: /profile', true, 303);
	exit;
}
//Hash new password
$passwordHash = password_hash($newPassword, PASSWORD_DEFAULT);

//Add new pasword to the database
$stmt = $pdo->prepare(
		'UPDATE users
		SET password = :password
		WHERE id = :id'
	);

$stmt->execute([
	'password' => $passwordHash,
	'id' => $_SESSION['user_id']
]);

header('Location: /profile?password-updated=1');
exit;