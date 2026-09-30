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

try{
//On faire request vers db pour supprimer image 
	$pdo->beginTransaction();

	$stmt = $pdo->prepare(
		'DELETE FROM images
		WHERE id = ? AND user_id =?'
	);

	$stmt->execute([
		$imageId,
		$_SESSION['user_id']
	]);	

	if ($stmt->rowCount() !== 1)//Si aucune ligne n'a été pas supprimé
	{
		$pdo->rollBack();

		echo json_encode([
			'success' => false,
			'message' => 'Impossible de trouver l\'image!'
		]);
		exit;
	}

	if (file_exists($imgPath) && !@unlink($imgPath))//Verification est ce que fichier existe, unlick on supprime le fichier et error si il n'arrive pas	{
	{
		$pdo->rollBack();

		echo json_encode([
			'success' => false,
			'message' => 'Impossible de supprimer le fichier, mais image retirée de la galerie!'
		]);
		exit;
	}

	$pdo->commit();
}
catch(PDOException $e)
{
	if ($pdo->inTransaction())
		$pdo->rollBack();

	echo json_encode([
		'success' => false,
		'message' => 'Impossible de supprimer image!'
	]);
	exit;
}




echo json_encode([
	'success' => true,
	'message' => 'Fichier supprimé',
]);