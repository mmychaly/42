<?php

require_once __DIR__  . '/../data/database.php';

// Get the requested gallery page and validate it.
$page = filter_input(INPUT_GET, 'page', FILTER_VALIDATE_INT);

if ($page === false ||$page === null ||$page < 1)
	$page = 1;

// Number of images displayed per page.
$numImgPage = 5;

$galleryError = null;

// Count the total number of gallery pages.
try {
	$stmt = $pdo->prepare(
		'SELECT COUNT(*) AS quantity
		FROM images'
	);

	$stmt->execute();
	$res = $stmt->fetch();

	// Count all images stored in the database.
	$totalImages = (int) $res['quantity'];// Number of images in the database.
	$totalPages = (int) ceil($totalImages / $numImgPage);// Total number of pages.

	// Prevent requests to non-existent pages.
	if ($totalPages > 0 && $page > $totalPages)
	$page = $totalPages;

	$calcPage =($page - 1) * $numImgPage; // Number of images to skip for pagination.

	// Load the images for the current page with the author's username
	// and the number of likes for each image.
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

	$stmt->bindValue(1, $numImgPage, PDO::PARAM_INT); // Bind the value as an integer.
	$stmt->bindValue(2, $calcPage, PDO::PARAM_INT);

	// INNER JOIN links each image with its author in the users table.

	$stmt->execute();
	$allImages = $stmt->fetchAll();

	// Comments.
	$comments = [];

	if (!empty($allImages))
	{
		$imageIds = [];

		foreach ($allImages as $image)
			$imageIds[] = (int) $image['id'];// IDs of all images on the current page.

		$preparePlaceholder = implode(',', array_fill(0, count($imageIds), '?'));
		
		// Load all comments belonging to the images displayed on the current page.
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

	// Likes.
	$likedImages = [];

	if (isset($_SESSION['user_id']) && !empty($allImages))
	{
		$imgIds = [];

		foreach ($allImages as $image)// IDs of all images on the current page.
		{
			$imgIds[] = (int) $image['id'];
		}

		$preparePlaceholder = implode(',', array_fill(0, count($imgIds), '?'));

		// Get the IDs of the displayed images already liked by the current user.
		$stmt = $pdo->prepare(
			"SELECT image_id
			FROM likes
			WHERE user_id = ?
			AND image_id IN ($preparePlaceholder)"
		);

		$args = [$_SESSION['user_id']];// First value: current user's ID.

		foreach ($imgIds as $imgId)
			$args[] = $imgId;// Following values: image IDs.

		$stmt->execute($args);

		$likedImages = $stmt->fetchAll();
		$likedImages = array_map('intval', array_column($likedImages, 'image_id'));
	}
}
catch(PDOException $e)
{
	$galleryError = 'Impossible de charger la galerie!';
	$allImages = [];
	$totalPages = 0;
} 

?>

<!-- Main page -->
<!DOCTYPE html>
<html lang="fr">
	<head>
		<meta charset="UTF-8">
		<meta name="viewport" content="width=device-width, initial-scale=1.0">
		<link rel="stylesheet" href="/css/site.css">
		<title>Galerie</title>
	</head>

	<body>
		<?php
			$headerPage = 'gallery';
			require __DIR__  . '/../common/header.php';
		?>

		<?php if (isUserSession()): ?>
			<input type="hidden" id="csrf-token" value="<?=htmlspecialchars(tokenCsrf()) ?>">
		<?php endif; ?>

		<main class="site-main gallery-layout">
			<h1>Galerie</h1>

			<?php if ($galleryError !== null): ?>
				<p class='form-error' role='alert'>
					<?= htmlspecialchars($galleryError) ?>
				</p>

			<?php elseif (empty($allImages)): ?>
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

							<button
								type="button"
								class='like-button'
								data-image-id="<?= (int) $image['id'] ?>"
							>
								<?= $hasLiked ? 'Retirer le like' : 'Like' ?>
							</button>

							<span class="error-massage" hidden></span>
						<?php endif; ?>

						<div class="comments">
							<h3>Commentaires</h3>

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

								<form
									class="form-comment"
									data-image-id="<?= (int) $image['id'] ?>"
									hidden
								>
									<label>
										Commentaire:
										<input
											type="text"
											name="message"
											class="comment-input"
											maxlength="400"
											required
										>
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

		<?php require __DIR__  . '/../common/footer.php'; ?>

		<script src="/js/gallery.js"></script>
	</body>
</html>