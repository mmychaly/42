<?php

require_once __DIR__  . '/../data/database.php';

$token = $_GET['token'] ?? '';
$linkError=null;//Variable dans laquelle on stock les erreur de lien transmit


$resetErrors = $_SESSION['reset_errors'] ?? [];//We receive errors from reset_check 
unset($_SESSION['reset_errors']);//Unset let clear variable $_SESSION['reset_errors']


//Ici on va verifier si le token de lien est conform  et nous avons ce token dans la db et est ce que il est toujour valide
if (!is_string($token) || strlen($token) !== 64 || !ctype_xdigit($token))//
{
	$linkError='Lien de réinitialisation invalide';
}
else
{
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

	if (!$user || strtotime($user['token_reset_expir_at']) <= time()) 
	{
		$linkError= "Lien de réinitialisation invalide ou expire.";
	}
}

?>

<!DOCTYPE html>
<html lang="fr">
<head>
	<meta charset="UTF-8">
	<meta name="viewport" content="width=device-width, initial-scale=1.0">
	<link rel="stylesheet" href="/css/site.css">
	<title>Mot de passe</title>
</head>
<body>
	<?php
		$headerPage = 'reset';
		require __DIR__  . '/../common/header.php';
	?>
	<main class="site-main auth-main">		
		<h1>Nouveau mot de passe</h1>

		<!-- Si le lien de réinitialisation n'est pas correct on affiche error sur la page -->
		<?php if($linkError !== null): ?>
			<p class="form-error" role="alert">
				<?= htmlspecialchars($linkError) ?>
			</p>
			<p>
				<a href="/password-forgot">Demander un nouveau lien</a>
			</p>
		<?php else:?>
			<?php if (!empty($resetErrors)): ?>
				<div class="form-error" role="alert">
					<?php foreach ($resetErrors as $error): ?>
						<p><?= htmlspecialchars($error) ?></p>
					<?php endforeach; ?>
				</div>
			<?php endif; ?>

			<form action="/password-reset" method="POST">
				<input type="hidden" name="token" value="<?= htmlspecialchars($token)?>">
				<input type="hidden" name="csrf_token" value="<?=htmlspecialchars(tokenCsrf()) ?>">
				<label for="password">Nouveau mot de passe</label>
				<input type="password" id="password" name="password" required>
				<p></p>
				<button type="submit">Modifier le mot de passe</button>
			</form>
		<?php endif; ?>
	</main>
	<?php require __DIR__  . '/../common/footer.php'; ?>
</body>
</html>