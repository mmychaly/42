<?php

require_once __DIR__  . '/../data/database.php';

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
	'SELECT id
	FROM likes
	WHERE user_id =?
	AND image_id = ?'
);

$stmt->execute([$_SESSION['user_id'], $imageId]);

$like = $stmt->fetch();

if ($like)
{
	$stmt = $pdo->prepare(
	'DELETE FROM likes
	WHERE id =?'
	);

	$stmt->execute([$like['id']]);

	$isLiked = false;
}
else
{
	$stmt = $pdo->prepare(
	'INSERT INTO likes (user_id, image_id)
	VALUES (?,?)'
	);

	$stmt->execute([$_SESSION['user_id'], $imageId]);

	$isLiked = true;
}

$stmt = $pdo->prepare(
	'SELECT COUNT(*) as quantity
		FROM likes
		WHERE image_id = ?'
	);

$stmt->execute([$imageId]);

$res = $stmt->fetch();

$likeNumber = (int) $res['quantity']; 

echo json_encode([
	'success' => true,
	'like' => $isLiked,
	'likeNumber' => $likeNumber
]);
