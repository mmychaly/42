<!DOCTYPE html>
<html lang="fr">
<head>
  <meta charset="UTF-8">
  <title>Formulaire POST multi TEXT/IMG</title></head>
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
      		border: none;
      		cursor: pointer;

			font-size: 16px;
			line-height: 1.2;
			font-weight: normal;
		}
		.btn:hover {
			background-color: rgba(9, 50, 91, 0.8);
		}
    input[type="file"] {
        margin: 20px 0;
    }
	</style>
</head>
<body>
  <h1>Upload a file</h1>
  <form method="POST" action="http://localhost:8001/php_cgi/post_multi.php" enctype="multipart/form-data">
	<input type="file" name="myfile"><br><br>
	<button class="btn" type="submit">Send file</button>
  </form>
</body>
</html>