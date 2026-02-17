import cgi
import os
import base64
import mimetypes
import html

fileName = ''
fileContent = ''
error = ''




if os.environ.get("REQUEST_METHOD") == "POST":
	form = cgi.FieldStorage()

	if "myfile" in form and form["myfile"].filename:
		filename = os.path.basename(form["myfile"].filename)
		upload_dir = os.environ.get("UPLOAD_PATH", os.path.join(os.getcwd(), "upl"))

		os.makedirs(upload_dir, exist_ok=True)

		filepath = os.path.join(upload_dir, filename)

		try:
			with open(filepath, 'wb') as f:
				f.write(form["myfile"].file.read())

			fileName = filename
			mime_type, _ = mimetypes.guess_type(filepath)

			if mime_type and mime_type.startswith("image/"):
				with open(filepath, "rb") as f:
					data = base64.b64encode(f.read()).decode("utf-8")
				fileContent = f"<img src='data:{mime_type};base64,{data}' style='max-width:600px; border-radius:10px;' />"	
		
			elif mime_type and mime_type.startswith("text/"):
				with open(filepath, "r", encoding="utf-8", errors="replace") as f:
					content = f.read()
				fileContent = f"<pre style='background-color: rgba(0, 0, 0, 0.5); padding: 30px; border-radius: 15px; text-align: left; white-space: pre-wrap; max-width: 800px; margin: 0 auto; font-size: 16px; line-height: 1.4;'>{html.escape(content)}</pre>"
			
			else:
				fileContent = f"<pre style='color: #ffaaaa; font-size: 18px;'>Type of file not supported : {mime_type or 'unknown'}</pre>"

		except Exception as e:
			error = "Error move uploaded file"
	else:
		error = "Error upload: no file received"
else:
	error = "Forbidden method"
print("""<!DOCTYPE html>
<html lang="fr">
<head>
	<meta charset="UTF-8">
	<title>File received</title>
	<style>
		body {
			font-family: sans-serif;
			display: flex;
			justify-content: center;
			align-items: center;
			min-height: 100vh;
			margin: 0;

			background-image: url('/py_cgi/py_img/background_py.avif');
			background-size: cover;
			background-position: center;
			background-repeat: no-repeat;
			color: white;
			padding: 20px;
			text-align: center;
		}
		.file-container {
			max-width: 900px;
			width: 100%;
		}
		.file-title {
			font-size: 28px;
			margin-bottom: 30px;
			color: white;
		}
		.file-name {
			font-size: 20px;
			margin-bottom: 30px;
			color: #ccddff;
			background-color: rgba(0, 0, 0, 0.7);
			padding: 20px;
			border-radius: 15px;
			word-break: break-all;
			border: 2px solid rgba(255, 255, 255, 0.3);
		}
		.file-content {
			margin-top: 20px;
		}
		.error-window {
			background-color: rgba(140, 0, 0, 0.8);
			padding: 20px;
			border-radius: 10px;
			color: #ffdddd;
			border:2px solid rgba(255, 0, 0, 0.5);
			margin: 0 auto;
		}
	</style>
</head>
<body>""")

if fileName and not error:
	print(f""" <div class="file-container">
	   <h1 class="file-title">File received:</h1>
	   <div class="file-name">{html.escape(fileName)}</div>
	   <div class="file-content">{fileContent}</div>
	   </div>""")
elif error:
	print(f'	<div class="error-window">{error}</div>')

print("""</body>
</html>""")