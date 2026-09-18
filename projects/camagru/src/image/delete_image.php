<?php

require_once __DIR__  . '/../data/database.php';

header('Content-Type: application/json; charset=utf-8');

$imageId = filter_input(INPUT_POST, 'image_id', FILTER_VALIDATE_INT);//Recuperer le id de image depuis body de post

if ($imageId === false || $imageId === null)//verification
{
		echo json_encode([
		'success' => false,
		'message' => 'Image invalide'
	]);
	exit;
}

//On va recuperer filename de image
$stmt = $pdo->prepare(
	'SELECT filename
	FROM images
	WHERE id = ? AND user_id = ?'
);

$stmt->execute([
	$imageId,
	$_SESSION['user_id']
]);

$image = $stmt->fetch();

if (!$image)
{
	echo json_encode([
		'success' => false,
		'message' => 'Impossible de trouver l\'image!'
	]);
	exit;
}

$imgPath = __DIR__ . '/../../uploads/' . $image['filename']; //on utilise le filename pour faire le path jusqu'a fichier

if (file_exists($imgPath))//Verification est ce que fichier existe
{
	if (!unlink($imgPath))//SI oui avec unlick on supprime le fichier
	{
		echo json_encode([
			'success' => false,
			'message' => 'Impossible de supprimer le fichier!'
		]);
		exit;
	}
}

//On faire request vers db pour supprimer image 
$stmt = $pdo->prepare(
	'DELETE FROM images
	WHERE id = ? AND user_id =?'
);

$stmt->execute([
	$imageId,
	$_SESSION['user_id']
]);


echo json_encode([
	'success' => true,
	'message' => 'Fichier supprimé'
]);