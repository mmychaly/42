<!DOCTYPE html>
<html>
<head><title>Formulaire POST simple</title></head>
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
<body>
  <h1>Send your message</h1>
  <form action="http://localhost:8001/php_cgi/post_simple.php" method="POST">
	<textarea name="message" rows="5" cols="40" placeholder="Type your message here"></textarea><br><br>
	<button class="btn" type="submit">Send</button>
  </form>
</body>
</html>