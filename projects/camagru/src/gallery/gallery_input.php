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
		users.username,
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


//comments
$comments = [];
if (!empty($allImages))
{
	$imageIds = [];

	foreach ($allImages as $image)
		$imageIds[] = (int) $image['id'];

	$preparePlaceholder = implode(',', array_fill(0, count($imageIds), '?'));

	$stmt = $pdo->prepare(
		"SELECT
			comments.id,
			comments.image_id,
			comments.message,
			comments.created_at,
			users.username
		FROM comments
		INNER JOIN users ON comments.user_id = users.id 
		WHERE comments.image_id IN ($preparePlaceholder)
		ORDER BY comments.created_at ASC, comments.id ASC"
	);

	$stmt->execute($imageIds);

	$comments = $stmt->fetchAll();
}





//likes
//On va chercher les id de l'images likes par utilisateur
$likedImages = [];

if (isset($_SESSION['user_id']) && !empty($allImages))
{
	$imgIds = [];

	foreach ($allImages as $image)//On va prendre tout les images de la page une par une
	{
		$imgIds[] = (int) $image['id'];//On recuper les id de images
	}

	$preparePlaceholder = implode(',', array_fill(0, count($imgIds), '?'));

	$stmt = $pdo->prepare(
		"SELECT image_id
		FROM likes
		WHERE user_id = ?
		AND image_id IN ($preparePlaceholder)"
	);
	$args = [$_SESSION['user_id']];

	foreach ($imgIds as $imgId)
		$args[] = $imgId;

		$stmt->execute($args);

		$likedImages = $stmt->fetchAll();
		$likedImages = array_map('intval', array_column($likedImages, 'image_id'));
}

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
						<p> Likes: 
							<span class="like-number"><?= (int) $image['like_number'] ?></span>
						</p>
						<?php if (isset($_SESSION['user_id'])): ?>
							<?php $hasLiked = in_array((int) $image['id'], $likedImages, true);?>
							<button type="button" class='like-button' data-image-id="<?= (int) $image['id'] ?>">
								<?= $hasLiked ? 'Retirer le like' : 'Like' ?>
							</button>
							<span class="error-massage" hidden></span>
						<?php endif; ?>
						<div class= "comments">
							<h2>Commentaires</h2>
							<?php foreach ($comments as $comment): ?>
								<?php if ((int) $comment['image_id'] === (int) $image['id']): ?>
									<div class="comment">
										<p>
											<strong><?= htmlspecialchars($comment['username']) ?></strong>
											:
											<?= htmlspecialchars($comment['message']) ?>
										</p>

										<small>
											<?= htmlspecialchars($comment['created_at']) ?>
										</small>
									</div>
								<?php endif;?>
							<?php endforeach; ?>
							<?php if (isset($_SESSION['user_id'])): ?>
								<button type="button" class="button-comment">
									Ajouter un commentaire:
								</button>

								<form class="form-comment" data-image-id="<?= (int) $image['id'] ?>" hidden>
									<label>
										Commentaire:
										<input type="text" name="message" class="comment-input" maxlength="400" required>
									</label>
									<button type="submit">
										Envoyer
									</button>
									<button type="button" class="cancel-comment">
										Annuler
									</button>
									<span class="msg-error-comment" hidden></span>
								</form>
							<?php endif; ?>
						</div>
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
		<script src="/js/gallery.js"></script>
	</body>
</html>