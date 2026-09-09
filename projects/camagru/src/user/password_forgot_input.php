<!DOCTYPE html>
<html lang="fr">
<head>
	<meta charset="UTF-8">
	<meta name="viewport" content="width=device-width, initial-scale=1.0">
	<title>Mot de passe oublié</title>
</head>
<body>
	<h1>Mot de passe oublié</h1>
	<form action="/password_forgot" method="POST">
		<label for="email">Email</label>
		<input type="email" id="email" name="email" required>
		<button type="submit">Réinitialiser mot de passe</button>
	</form>
</body>
</html>