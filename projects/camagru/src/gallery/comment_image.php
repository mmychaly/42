<?php

require_once __DIR__  . '/../data/database.php';
require_once __DIR__  . '/../common/mail.php';

header('Content-Type: application/json; charset=utf-8');

$imageId = filter_input(INPUT_POST, 'image_id', FILTER_VALIDATE_INT);// Get the image ID from the POST request body.


if ($imageId === false || $imageId === null || $imageId < 1)// Validate the image ID.
{
		echo json_encode([
			'success' => false,
			'message' => 'Image invalide'
	]);
	exit;
}

$message = $_POST['message'] ?? '';

if (!is_string($message))
{
	echo json_encode([
		'success' => false,
		'message' => 'Commentaire invalide!'
	]);
	exit;
}

$message = trim($message);

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

try{
	$stmt = $pdo->prepare(
	'SELECT 
		images.id,
		users.username,
		users.email,
		users.email_notif
	FROM images
	INNER JOIN users ON images.user_id = users.id
	WHERE images.id = ?'
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
}catch (PDOException $e)
{
	echo json_encode([
			'success' => false,
			'message' => 'Impossible traiter le commentaire'
	]);
	exit;
}


try {
	$stmt = $pdo->prepare(
		'INSERT INTO comments (image_id, user_id, message)
		VALUES (?,?,?)'
	);

	$stmt->execute([$imageId, $_SESSION['user_id'], $message]);

	$commentId = (int) $pdo->lastInsertId();
}
catch (PDOException $e)
{
	echo json_encode([
			'success' => false,
			'message' => 'Impossible de traiter le commentaire'
	]);
	exit;
}


if ((int) $image['email_notif'] === 1)
{
	sendCommentEmail($image['username'], $image['email']);
}



// Get the complete information for the newly created comment.
try{
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

	if (!$comment)
	{
		echo json_encode([
				'success' => false,
				'message' => 'Impossible de récupérer le commentaire!'
		]);
		exit;
}	
}catch (PDOException $e)
{
	echo json_encode([
			'success' => false,
			'message' => 'Impossible traiter le commentaire'
	]);
	exit;
}


// Return the comment data to JavaScript for display.
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