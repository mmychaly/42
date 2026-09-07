<!DOCTYPE html>
<html lang="fr">
	<head>
		<meta charset="UTF-8">
		<meta name="viewport" content="width=device-width, initial-scale=1.0">
		<title>Inscription</title>
	</head>
	<body>
		<h1>Créer un compte</h1>
		<form action="/register" method="POST">
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
	</body>
</html>