<!DOCTYPE html>
<html lang="fr">
<head>
	<meta charset="UTF-8">
	<title>Welcome to our website for webserver project</title>
	<style>
		body {
			font-family: sans-serif;
			text-align: center;
			margin-top: 80px;

			background-image: url('/php_cgi/php_img/background_php.avif');
			background-size: cover;
			background-position: center;
			background-repeat: no-repeat;
			color: white;
		}
		.btn {
			display: inline-block;
			padding: 10px 20px;
			margin: 10px;
			background-color: rgba(9, 50, 91, 0.8);
			color: white;
			text-decoration: none;
			border-radius: 5px;
		}
		.btn:hover {
			background-color: rgba(9, 50, 91, 0.8);
		}
	</style>
</head>
<body>
	<h1>Hi my friend</h1>
	<p>It's PHP script!</p>
	<p>Choose an action :</p>
	<a class="btn" href="/php_cgi/post_simple_form.php">Send a text message</a>
	<a class="btn" href="/php_cgi/post_multi_form.php">Upload files</a>
</body>
</html>
