<!DOCTYPE html>
<html lang="fr">
<head>
	<meta charset="UTF-8">
	<meta name="viewport" content="width=device-width, initial-scale=1.0">
	<title>Connexion</title>
</head>
<body>
	<?php if (isset($_GET['registered'])): ?>
		<p>Compte créé avec succès. Vous pouvez vous connecter.</p>
	<?php endif; ?>
	
	<h1>Connexion</h1>

	<form action="/login" method="POST">
		<label for="username">Nom d'utilisateur</label>
		<input type="text" id="username" name="username" required>
		<p></p>
		<label for="password">Mot de passe</label>
		<input type="password" id="password" name="password" required>
		<p></p>
		<button type="submit">Se connecter</button>
	</form>

	<?php if (isset($_GET['verified'])): ?>
		<p>L'email a été vérifié. Vous pouvez vous connecter.</p>
	<?php endif; ?>
</body>
</html>