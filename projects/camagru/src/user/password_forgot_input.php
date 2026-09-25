<?php
$forgotError = $_SESSION['forgot_error'] ?? null;
$forgotSuccess = $_SESSION['forgot_success'] ?? null;

unset($_SESSION['forgot_error'], $_SESSION['forgot_success']);
?>

<!DOCTYPE html>
<html lang="fr">
<head>
	<meta charset="UTF-8">
	<meta name="viewport" content="width=device-width, initial-scale=1.0">
	<link rel="stylesheet" href="/css/site.css">
	<title>Mot de passe oublié</title>
</head>
<body>
	<?php
		$headerPage = 'forgot';
		require __DIR__  . '/../common/header.php';
	?>
	<main class="site-main auth-main">
		<h1>Mot de passe oublié</h1>
		<?php if ($forgotError !== null): ?>
				<p class="form-error" role="alert">
					<?= htmlspecialchars($forgotError) ?>
				</p>
		<?php endif; ?>

		<?php if ($forgotSuccess !== null): ?>
			<p role="status"><?= htmlspecialchars($forgotSuccess) ?></p>
		<?php endif; ?>

		<form action="/password-forgot" method="POST">
			<input type="hidden" name="csrf_token" value="<?=htmlspecialchars(tokenCsrf()) ?>">
			<label for="email">Votre email</label>
			<input type="email" id="email" name="email" required>
			<p></p>
			<button type="submit">Réinitialiser mot de passe</button>
		</form>
	</main>
	<?php require __DIR__  . '/../common/footer.php'; ?>
</body>
</html>