<?php

header('Content-Type: application/json');

if (!isset($_FILES['image']) || !isset($_POST['overlay']))
{
	echo json_encode([
		'success' => false,
		'message' => 'Image ou overlay absent'
	]);
	exit;
}

$file = $_FILES['image'];
$overlay = $_POST['overlay'];

if ($file['error'] !== UPLOAD_ERR_OK)
{
	echo json_encode([
		'success' => false,
		'message' => 'Erreur pendant chargment'
	]);
	exit;
}



echo json_encode([
	'success' => true,
	'message' => 'Fichier est bien chargé',
	'overlay' => $overlay,
	'file_size' => $file['size']
]);