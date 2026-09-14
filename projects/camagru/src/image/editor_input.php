<?php

require_once __DIR__  . '/../data/database.php';

$stmt = $pdo->prepare(
	'SELECT id, filename, created_at
	FROM images
	WHERE user_id = ?
	ORDER BY created_at  DESC
	LIMIT 5'
);

$stmt->execute([$_SESSION['user_id']]);
$userImages = $stmt->fetchAll();
?>

<!DOCTYPE html>
<html lang="fr">
<head>
	<meta charset="UTF-8">
	<meta name="viewport" content="width=device-width, initial-scale=1.0">
	<link rel="stylesheet" href="/css/editor.css">

	<title>Créer une image</title>
</head>
<body>
	<h1>Créer une image</h1>
	<main>
		<section>
			<h2>Zone de prévisualisation</h2>

			<div id="preview">
				<p id="preview-text">La camera ou l'image sera ici</p>
				<img id = "preview-image" src="" alt="Image chargée" hidden>
				<img id = "preview-overlay" src="" alt="Overlay ajouté" hidden>
			</div>
			<label for="image-load">Choisir une image :</label>
			<input type="file" id="image-load" accept="image/png, image/jpeg">

			<!-- overlay -->
			<div id="overlay-list">
				<h2>Choisissez un overlay</h2>
				<button type="button" class="overlay" data-overlay="cat.png">
					<img src="/asset/image-def/cat.png" width="100" height="100">		
				</button>
				<button type="button" class="overlay" data-overlay="crown.png">
					<img src="/asset/image-def/crown.png"  width="100">
				</button>
				<button type="button" class="overlay" data-overlay="glasses.png">
					<img src="/asset/image-def/glasses.png" alt="Lunettes" width="100">		
				</button>
			</div>

			<!-- Capture -->
			<button type="button" id="capture-button" disabled>
				Prendre la photo
			</button>
		</section>

		<aside>
			<h2>Dernières photos crées</h2>

			<div id="user-images">
				<?php if (empty($userImages)): ?>
					<p>Aucune image.</p>
				<?php else: ?>
					<?php foreach ($userImages as $image): ?>
						<img src="/uploads/<?=htmlspecialchars($image['filename'])?>" width="150">
					<?php endforeach; ?>
				<?php endif; ?>
			</div>
		</aside>
	</main>
	<script src="/js/editor.js"></script>
</body>

</html>