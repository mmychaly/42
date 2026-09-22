<?php

require_once __DIR__  . '/../data/database.php';

header('Content-Type: application/json; charset=utf-8');

$imageId = filter_input(INPUT_POST, 'image_id', FILTER_VALIDATE_INT);//Recuperer le id de image depuis body de post
$message = trim($_POST['message'] ?? '');

if ($imageId === false || $imageId === null || $imageId < 1)//verification
{
		echo json_encode([
			'success' => false,
			'message' => 'Image invalide'
	]);
	exit;
}

if ($message === '')
{
	echo json_encode([
		'success' => false,
		'message' => 'Commentaire vide!'
	]);
	exit;
}

if (strlen($message) > 400)
{
	echo json_encode([
		'success' => false,
		'message' => 'Commentaire trop long!'
	]);
	exit;	
}

$stmt = $pdo->prepare(
	'SELECT id
	FROM images
	WHERE id =?'
);

$stmt->execute([$imageId]);

$image = $stmt->fetch();

if (!$image)
{
	echo json_encode([
			'success' => false,
			'message' => 'Image introuvable'
	]);
	exit;
}

$stmt = $pdo->prepare(
	'INSERT INTO comments (image_id, user_id, message)
	VALUES (?,?,?)'
	);

$stmt->execute([$imageId, $_SESSION['user_id'], $message]);

$commentId = (int) $pdo->lastInsertId();

//On fait request pour recuperer information complete de commentaire
$stmt = $pdo->prepare(
	'SELECT
		comments.id,
		comments.image_id,
		comments.message,
		comments.created_at,
		users.username
		FROM comments
		INNER JOIN users ON comments.user_id = users.id
		WHERE comments.id = ?'
);

$stmt->execute([$commentId]);
$comment = $stmt->fetch();

echo json_encode([
	'success' => true,
	'message' => "Commentaire ajouté",
	'comment' => [
		'id' => (int) $comment['id'],
		'imageId' => (int) $comment['image_id'],
		'message' => $comment['message'],
		'createdAt' => $comment['created_at'],
		'username' => $comment['username']
	]
]);