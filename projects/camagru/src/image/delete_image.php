<?php

require_once __DIR__  . '/../data/database.php';

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

// Get the filename of the image owned by the current user.
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

$imgPath = __DIR__ . '/../../uploads/' . $image['filename']; // Build the path to the image file using its filename.

try
{
	// Start a transaction before deleting the image from the database.
	$pdo->beginTransaction();

	$stmt = $pdo->prepare(
		'DELETE FROM images
		WHERE id = ? AND user_id =?'
	);

	$stmt->execute([
		$imageId,
		$_SESSION['user_id']
	]);	

	if ($stmt->rowCount() !== 1)// If no row was deleted, cancel the transaction.
	{
		$pdo->rollBack();

		echo json_encode([
			'success' => false,
			'message' => 'Impossible de trouver l\'image!'
		]);

		exit;
	}

	if (file_exists($imgPath) && !@unlink($imgPath))// If the file exists, delete it. Roll back if the deletion fails.
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