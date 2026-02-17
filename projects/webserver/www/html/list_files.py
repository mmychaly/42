import cgi
import os
import json
import sys


try:
	UPLOAD_PATH = os.environ.get("UPLOAD_PATH", os.path.join(os.getcwd(), "uploads"))

	tmp = os.path.basename(UPLOAD_PATH)

	if tmp == "html":
		WEB_PATH = "/"
	else:
		WEB_PATH = "/" + tmp.strip("/") + "/"

	files = []
	for f in os.listdir(UPLOAD_PATH):
		if f.lower().endswith((".jpg", ".jpeg", ".png", ".gif", ".avif")):
			files.append({
				"name": f,
				"url": f"{WEB_PATH}{f}"
			})

	print(json.dumps(files))

except Exception as e:
    print("Content-Type: text/plain\n")
    print("Error in CGI:", e, file=sys.stderr)
    print("Error:", str(e))
