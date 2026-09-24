<!DOCTYPE html>
<html lang="fr">
<head>
	<meta charset="UTF-8">
	<meta name="viewport" content="width=device-width, initial-scale=1.0">
	<title>Connexion</title>
</head>
<body>
	<?php if (isset($_GET['registered'])): ?>
		<p>Compte créé avec succès. Avant vous connecter, consultez votre email pour valider le compte.</p>
	<?php endif; ?>
	
	<h1>Connexion</h1>

	<form action="/login" method="POST">
		<input type="hidden" name="csrf_token" value="<?=htmlspecialchars(tokenCsrf()) ?>">
		<label for="username">Nom d'utilisateur</label>
		<input type="text" id="username" name="username" required>
		<p></p>
		<label for="password">Mot de passe</label>
		<input type="password" id="password" name="password" required>
		<p></p>
		<button type="submit">Se connecter</button>
	</form>
	<!-- add p here? -->
	<p>
		<a href="/password-forgot">Mot de passe oublié?</a>
	</p>
	<!-- add p here? -->
	<?php if (isset($_GET['verified'])): ?>
		<p>L'email a été vérifié. Vous pouvez vous connecter.</p>
	<?php endif; ?>
	<?php if (isset($_GET['password-reset'])): ?>
		<p>Votre mot de pass a été modifié. Vous pouvez vous connecter.</p>
	<?php endif; ?>
</body>
</html>