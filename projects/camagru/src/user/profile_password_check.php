<?php

require_once __DIR__  . '/../data/database.php';

$currentPassword = $_POST['current_password'] ?? '';
$newPassword = $_POST['new_password'] ?? '';
$confirmPassword = $_POST['confirm_password'] ?? '';

$error = [];


if ($currentPassword === '')
{
	$error[] = "Le mot de passe actuel est obligatoire!";
}

if ($newPassword === '')
{
	$error[] = "Le mot de passe actuel est obligatoire!";
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
	foreach ($error as $erro) {
		echo htmlspecialchars($erro) . '<br>';
	}
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
	echo 'Utilisateur introuvable';
	exit;
}

if (!password_verify($currentPassword, $user['password'])) {
	echo 'Le mot de passe actuel est incorrect!';
	exit;
}

if (password_verify($newPassword, $user['password'])) {
	echo 'Le nouveau mot de passe doit etre différent du mot de passe actuel!';
	exit;
}

$passwordHash = password_hash($newPassword, PASSWORD_DEFAULT);
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