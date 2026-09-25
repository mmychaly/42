<?php
$headerPage = $headerPage ?? 'gallery';
?>

<header class="common-header">
	<a href="/" class="site-logo">CAMAGRU</a>
	<nav class="site-nav" aria-label="Navigation principale">
		<a href="/">Galerie</a>

		<?php if ($headerPage === 'login'): ?>
			<a href="/register">Inscription</a>
		<?php elseif ($headerPage === 'register'): ?>
			<a href="/login">Connexion</a>
		<?php elseif (in_array($headerPage, ['forgot', 'reset'], true)): ?>
			<a href="/login">Connexion</a>
			<a href="/register">Inscription</a>

		<?php elseif (isUserSession()): ?>
			<?php if ($headerPage !== 'editor'): ?>
				<a href="/editor">Editeur</a>
			<?php endif; ?>

			<?php if ($headerPage !== 'profile'): ?>
				<a href="/profile">Profil</a>
			<?php endif; ?>	


			<form action="/logout" method="POST">
				<input type="hidden" name="csrf_token" value="<?=htmlspecialchars(tokenCsrf()) ?>">
				<button type="submit">Déconnexion</button>
			</form>
		<?php else: ?>
			<a href="/login">Connexion</a>
			<a href="/register">Inscription</a>
		<?php endif; ?>
	</nav>
</header>