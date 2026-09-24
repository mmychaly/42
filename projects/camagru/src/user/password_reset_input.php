<?php

require_once __DIR__  . '/../data/database.php';

$token = $_GET['token'] ?? '';

if (!is_string($token) || strlen($token) !== 64 || !ctype_xdigit($token))
{
	http_response_code(400);
	exit('Token de réinitialisation invalide');
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
		<input type="hidden" name="csrf_token" value="<?=htmlspecialchars(tokenCsrf()) ?>">
		<p></p>
		<label for="password">Nouveau mot de passe</label>
		<input type="password" id="password" name="password" required>
		<button type="submit">Modifier le mot de passe</button>
	</form>
</body>
</html>