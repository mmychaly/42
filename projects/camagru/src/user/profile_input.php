<?php
$profileErrors = $_SESSION['profile_errors'] ?? [];
$profilePasswordErrors = $_SESSION['profile_password_errors'] ?? [];

unset($_SESSION['profile_errors'], $_SESSION['profile_password_errors']);
?>

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
	unset($_SESSION['user_id'], $_SESSION['username']);
	$_SESSION['login_error'] = "Votre compte est introuvable.Veuillez vous recconnecter.";
	header('Location: /login', true, 303);
	exit;
}

?>

<!DOCTYPE html>
<html lang='fr'>
<head>
	<meta charset="UTF-8">
	<meta name="viewport" content="width=device-width, initial-scale=1.0">
	<link rel="stylesheet" href="/css/site.css">
	<title>Profil</title>
</head>
<body>
	<?php
		$headerPage = 'profile';
		require __DIR__  . '/../common/header.php';
	?>
	<main class="site-main profile-main">
		<h1>Mon profil</h1>

		<?php if (isset($_GET['email-verified'])): ?>
			<p role='status'>L'email a été vérifié avec succes.</p>
		<?php endif; ?>

		<?php if (!empty($profileErrors)): ?>
			<div class="form-error" role="alert">
				<?php foreach ($profileErrors as $error): ?>
					<p><?= htmlspecialchars($error) ?></p>
				<?php endforeach; ?>
			</div>
		<?php endif; ?>

		<form action="/profile" method="POST">
			<input type="hidden" name="csrf_token" value="<?=htmlspecialchars(tokenCsrf()) ?>">	
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
		<?php if (!empty($profilePasswordErrors)): ?>
			<div class="form-error" role="alert">
				<?php foreach ($profilePasswordErrors as $error): ?>
					<p><?= htmlspecialchars($error) ?></p>
				<?php endforeach; ?>
			</div>
		<?php endif; ?>

		<form action="/profile/password" method="POST">
			<input type="hidden" name="csrf_token" value="<?=htmlspecialchars(tokenCsrf()) ?>">
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
	</main>
	<?php require __DIR__  . '/../common/footer.php'; ?>
	</body>
</html>