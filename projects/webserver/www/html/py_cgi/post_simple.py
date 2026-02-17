import cgi
import os
import html


msg = ''
error = ''

if os.environ.get("REQUEST_METHOD") == "POST":
	form = cgi.FieldStorage()
	msg = form.getvalue("message", "")
	if msg == "":
		error = "No message received!"
else:
	error = "Error: unauthorized method!"

print("""<!DOCTYPE html>
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

			background-image: url('/py_cgi/py_img/background_py.avif');
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
	  	.error-window {
	  		background-color: rgba(139, 0, 0, 0.8);
			padding: 20px;
			border-radius: 10px;
			max-width: 400px;
	  		color: #ffdddd;
	  		border:2px solid rgba(255, 0, 0, 0.5);
	  	}
	</style>
</head>
<body>""")

if msg:
	print(f""" <div class="message-container">
	   <h1 class="message-title">Message received:</h1>
	   <div class="message-window">{html.escape(msg).replace(chr(10), '<br>')}</div>
	</div>""")
elif error:
		print(f'	<div class="error-window">{error}</div>')

print("""</body>
</html>""")