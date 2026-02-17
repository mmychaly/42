<?php

function isTextFile($filePath) {
	$sample = file_get_contents($filePath, false, null, 0, 512);
	return preg_match('//u', $sample) && !preg_match('/[^\x09\x0A\x0D\x20-\x7E]/', $sample);//проверяем на нечитаемые символы
}

$fileName = '';
$fileContent = '';
$error = '';


if ($_SERVER["REQUEST_METHOD"] == "POST") {
	if ($_FILES['myfile']['error'] === UPLOAD_ERR_OK) {
		$tmp = $_FILES['myfile']['tmp_name'];
		$name = basename($_FILES['myfile']['name']);
		$upload_dir = getenv('UPLOAD_PATH') ?: __DIR__ . "/";
		$dest =  $upload_dir . "/" . $name;

		if (!is_dir($upload_dir)) {
			mkdir($upload_dir, 0777, true);
		}

		if (move_uploaded_file($tmp, "$dest"))
		{
			$fileName = $name;

			$mime = mime_content_type($dest);

			if (str_starts_with($mime, "image/")) {
				$data = base64_encode(file_get_contents($dest));
				$fileContent = "<img src='data:$mime;base64,$data' style='max-width:600px; border-radius:10px;' />";
			} elseif (isTextFile($dest)) {
				$contenu = htmlspecialchars(file_get_contents($dest)) ;
				$fileContent = "<pre style='background-color: rgba(0,0,0,0.5); padding: 30px; border-radius: 15px; text-align: left; white-space: pre-wrap; max-width: 800px; margin: 0 auto; font-size: 16px; line-height: 1.4;'>$contenu</pre>";
			} else {
				$fileContent = "<pre style='color: #ffaaaa; font-size: 18px;'>Type of file not supported : $mime</pre>";
			}
		} else {
			$error = "Error move uploaded file";
		}
	} else {
		$error = "Error upload : code " . $_FILES['myfile']['error'];
	}
} else {
	$error = "Forbidden method";
}
?>
<!DOCTYPE html>
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

			background-image: url('/php_cgi/php_img/background_php.avif');
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
<body>
	<?php if ($fileName && !$error): ?>
		<div class="file-container">
			<h1 class="file-title">File received:</h1>
			<div class="file-name"><?= htmlspecialchars($fileName) ?></div>
			<div class="file-content"><?= $fileContent ?></div>
		</div>
	<?php elseif ($error): ?>
		<div class="error-window"><?= $error ?></div>
	<?php endif; ?>
</body>
</html>
