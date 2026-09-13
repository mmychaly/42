<?php

require_once __DIR__  . '/../data/database.php';

$token = $_GET['token'] ?? '';

if ($token === '') {
	echo 'Token de réinitialisation est absent!';
	exit;
}

$tokenHash = hash('sha256', $token);

$stmt = $pdo->prepare(
	'SELECT id, token_reset_expir_at
	FROM users
	WHERE token_reset = :token_reset'
);

$stmt->execute([
	'token_reset' => $tokenHash
]);

$user = $stmt->fetch();

if (!$user) {
	echo 'Lien de réinitialisation invalide.';
	exit;
}

if (strtotime($user['token_reset_expir_at']) < time())
{
	echo 'Le lien de réinitialisation a expiré!';
	exit;
}
?>

<!DOCTYPE html>
<html lang="fr">
<head>
	<meta charset="UTF-8">
	<meta name="viewport" content="width=device-width, initial-scale=1.0">
	<title>Mot de passe</title>
</head>
<body>
	<h1>Nouveau mot de passe</h1>
	<form action="/password-reset" method="POST">
		<input type="hidden" name="token" value="<?= htmlspecialchars($token)?>">
		<p></p>
		<label for="password">Nouveau mot de passe</label>
		<input type="password" id="password" name="password" required>
		<button type="submit">Modifier le mot de passe</button>
	</form>
</body>
</html>