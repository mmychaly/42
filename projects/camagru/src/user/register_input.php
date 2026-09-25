<?php
$registerErrors = $_SESSION['register_errors'] ?? [];

unset($_SESSION['register_errors']);
?>

<!DOCTYPE html>
<html lang="fr">
	<head>
		<meta charset="UTF-8">
		<meta name="viewport" content="width=device-width, initial-scale=1.0">
		<link rel="stylesheet" href="/css/site.css">
		<title>Inscription</title>
	</head>
	<body>
		<?php
			$headerPage = 'register';
			require __DIR__  . '/../common/header.php';
		?>
		<main class="site-main auth-main">
			<h1>Créer un compte</h1>
			<?php if (!empty($registerErrors)): ?>
				<div class="form-error" role="alert">
					<?php foreach ($registerErrors as $error): ?>
						<p><?= htmlspecialchars($error) ?></p>
					<?php endforeach; ?>
				</div>
			<?php endif; ?>
		
			<form action="/register" method="POST">
				<input type="hidden" name="csrf_token" value="<?=htmlspecialchars(tokenCsrf()) ?>">
				<label for="username">Nom d'utilisateur</label>
				<input
					type="text"
					id="username"
					name="username"
					required
				>
				<p></p>
				<label for="email">Email</label>
				<input
					type="email"
					id="email"
					name="email"
					required
				>
				<p></p>
				<label for="password">Mot de passe</label>
				<input
					type="password"
					id="password"
					name="password"
					required
				>
				<p></p>
				<button type="submit">Envoyer</button>
			</form>
		</main>
		<?php require __DIR__  . '/../common/footer.php'; ?>
	</body>
</html>