<?php

require_once __DIR__  . '/../data/database.php';

//Ici on recuper les données d'utilisteur
$stmt = $pdo->prepare(
	'SELECT username, email, email_notif
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

?>

<!DOCTYPE html>
<html lang='fr'>
<head>
	<meta charset="UTF-8">
	<meta name="viewport" content="width=device-width, initial-scale=1.0">
	<title>Profil</title>
</head>
<body>
	<h1>Mon profil</h1>

	<form action="/profile" method="POST">
		<label for="username">Nom d'utilisatateur</label>
		<input type="text" 
				id="username" 
				name="username" 
				value="<?= htmlspecialchars($user['username']) ?>"
				required
		>

		<br>
		<label for="email">Email</label>
		<input type="email" 
				id="email" 
				name="email" 
				value="<?= htmlspecialchars($user['email']) ?>"
				required
		>
		<br>
		<label>
			<input
				type="checkbox"
				name="email_notif"
				<?= $user['email_notif'] ? 'checked' : '' ?>
			>
		Recevoir une notification lorsqu'une personne commente les photos
		</label>
		<br>
		<button type="submit">Enregistrer</button>
	</form>

	<h2>Modifier le mot de passe</h2>
	<form action="/profile/password" method="POST">
		<label for="current_password">Mot de passe actuel</label>
		<input type="password" id="current_password" name="current_password" required>
		<br>
		<label for="new_password">Nouveau mot de passe</label>
		<input type="password" id="new_password" name="new_password" required>
		<br>
		<label for="confirm_password">Confirmer le nouveau mot de passe</label>
		<input type="password" id="confirm_password" name="confirm_password" required>
		<br>
		<button type="submit">Modifer le mot de passe</button>
	</form>
	<?php if (isset($_GET['password-updated'])): ?>
		<p>Mot de passe a été modifié avec succés!</p>
	<?php endif; ?>
	</body>
</html>