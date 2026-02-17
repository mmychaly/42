<?php

$msg = '';
$error = '';

if ($_SERVER['REQUEST_METHOD'] === 'POST') {
	$msg = htmlspecialchars($_POST['message'] ?? '');
	if ($msg === '') {
		$error = "No message received!";
	}
} else {
	$error = "Error : unauthorized method!";
}
?>
<!DOCTYPE html>
<html lang="fr">
<head>
	<meta charset="UTF-8">
	<title>POST simple</title>
	<style>
		body {
			font-family: sans-serif;
			display: flex;
			justify-content: center;
			align-items: center;
			height: 100vh;
			margin: 0;

			background-image: url('/php_cgi/php_img/background_php.avif');
			background-size: cover;
			background-position: center;
			background-repeat: no-repeat;
			color: white;
			text-align: center;
		}
		.message-container {
			text-align: center;
		}

		.message-title {
			font-size: 24px;
			margin-bottom: 20px;
			color: white;
		}
		.message-window {
			background-color: rgba(0, 0, 0, 0.7);
			padding: 40px;
			border-radius: 15px;
			max-width: 600px;
			min-height: 100px;
			font-size: 18px;
			color: #f0f0f0;
			text-align: left;
			white-space: pre-wrap;
			border:2px solid rgba(255, 255, 255, 0.3);
		}
	</style>
</head>
<body>
		<?php if ($msg): ?>
			<div class="message-container">
				<h1 class="message-title">Message received:</h1>
				<div class="message-window"><?= nl2br($msg) ?></div>
		<?php elseif ($error): ?>
			<p><?= $error ?></p>
		<?php endif; ?>
</body>
</html>