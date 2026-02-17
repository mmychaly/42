print("""<!DOCTYPE html>
<html lang="fr">
<head>
	<meta charset="UTF-8">
	<title>Formulaire POST multi TEXT/IMG</title>
	<style>
		body {
			font-family: sans-serif;
			text-align: center;
			margin-top: 80px;

			background-image: url('/py_cgi/py_img/background_py.avif');
			background-size: cover;
			background-position: center;
			background-repeat: no-repeat;
			color: white;
		}
		.btn {
			display: inline-block;
			padding: 10px 20px;
			margin: 10px;
			background-color: rgba(44, 55, 67, 0.8);
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
			background-color: rgba(44, 55, 67, 0.8);
		}
    input[type="file"] {
        margin: 20px 0;
    }
	</style>
</head>
<body>
  <h2>Upload a file</h2>
  <form method="POST" action="http://localhost:8001/py_cgi/post_multi.py" enctype="multipart/form-data">
	<input type="file" name="myfile"><br><br>
	<button class="btn" type="submit">Send file</button>
  </form>
</body>
</html>
""")