<?php

require_once __DIR__  . '/../data/database.php';

$page = filter_input(INPUT_GET, 'page', FILTER_VALIDATE_INT);

if ($page === false ||$page === null ||$page < 1)
	$page = 1;

$numImgPage = 5;

//Bloc pour conter nombre de pages de galerie
// 1)Request for the db , to count all images in the db
$stmt = $pdo->prepare(
	'SELECT COUNT(*) AS quantity
	FROM images'
);

$stmt->execute();
$res = $stmt->fetch();

$totalImages = (int) $res['quantity'];// 2)Number of images in db, type int
$totalPages = (int) ceil($totalImages / $numImgPage);// 3)Total number of pages

//Protection against request to  page non-existent
if ($totalPages > 0 && $page > $totalPages)
	$page = $totalPages;

$calcPage =($page - 1) * $numImgPage; //On calcule sur que contité de image il faut passer à une l'autre

//4)Request to recive all data for each image, with a limit 5 images and an offset for pagination
$stmt = $pdo->prepare(
	'SELECT 
		images.id,
		images.filename,
		images.created_at,
		users.username
		(
			SELECT COUNT(*)
			FROM likes
			WHERE likes.image_id = images.id
		) AS like_number
	FROM images
	INNER JOIN users ON images.user_id = users.id 
	ORDER BY images.created_at DESC, images.id DESC
	LIMIT ? OFFSET ?'
);

$stmt->bindValue(1, $numImgPage, PDO::PARAM_INT); //On utilise ca pour etre sur d'envoier int
$stmt->bindValue(2, $calcPage, PDO::PARAM_INT);

//INNER JOIN users ON images.user_id = users.id // On va fussioner images et users

$stmt->execute();

$allImages = $stmt->fetchAll();

?>

<!DOCTYPE html>
<html lang=fr>
	<head>
		<meta charset="UTF-8">
		<meta name="viewport" content="width=device-width, initial-scale=1.0">
		<title>Galerie</title>
	</head>

	<body>
		<h1>Galerie</h1>

		<main>
			<?php if (empty($allImages)): ?>
				<p>Aucune image dans la galerie</p>
			<?php else: ?>
				<?php foreach ($allImages as $image): ?>
					<article class="gallery-image">
						<img 
								src="/uploads/<?=htmlspecialchars($image['filename'])?>" 
								alt="Image de <?=htmlspecialchars($image['username'])?>" 
								width="400">
						<p> Crée par <?=htmlspecialchars($image['username'])?> </p>
						<p> Date: <?=htmlspecialchars($image['created_at'])?> </p>
					</article>
				<?php endforeach; ?>
 			<?php endif; ?>
			<?php if ($totalPages > 1): ?>
				<nav class="pagination">

					<?php if ($page > 1): ?>
						<a href="/image/gallery?page=<?= $page - 1 ?>">
							Précédent
						</a>
					<?php endif; ?>

					<?php for ($i = 1; $i <= $totalPages; $i++): ?>
						<?php if ($i === $page): ?>
							<span class="current-page">
								<?= $i ?>
							</span>
						<?php else: ?>
							<a href="/image/gallery?page=<?= $i ?>">
								<?= $i ?>
							</a>
						<?php endif;?>
					<?php endfor; ?>
					
					<?php if ($page < $totalPages): ?>
						<a href="/image/gallery?page=<?= $page + 1 ?>">
							Suivant
						</a>
					<?php endif; ?>
				</nav>
			<?php endif; ?>
		</main>
	</body>
</html>