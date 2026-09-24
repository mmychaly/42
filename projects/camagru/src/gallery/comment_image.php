<?php

require_once __DIR__  . '/../data/database.php';
require_once __DIR__  . '/../common/mail.php';

header('Content-Type: application/json; charset=utf-8');

$imageId = filter_input(INPUT_POST, 'image_id', FILTER_VALIDATE_INT);//Recuperer le id de image depuis body de post


if ($imageId === false || $imageId === null || $imageId < 1)//verification
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
	http_response_code(400);
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

$stmt = $pdo->prepare(
	'INSERT INTO comments (image_id, user_id, message)
	VALUES (?,?,?)'
	);

$stmt->execute([$imageId, $_SESSION['user_id'], $message]);

$commentId = (int) $pdo->lastInsertId();

if ((int) $image['email_notif'] === 1)
{
	sendCommentEmail($image['username'], $image['email']);
}



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

//on va retourner le data vers js pour afficher les données
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