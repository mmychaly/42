print("""<!DOCTYPE html>
<html>
<head><title>Formulaire POST simple</title></head>
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
	  
<body>
  <h2>Send your message</h2>
  <form action="http://localhost:8001/py_cgi/post_simple.py" method="POST">
	<textarea name="message" rows="5" cols="40" placeholder="Type your message here"></textarea><br><br>
	<button class="btn" type="submit">Send</button>
  </form>
</body>
</html>
""")