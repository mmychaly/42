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

