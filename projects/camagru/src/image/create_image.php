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

//Interdiction de image trop lourde <5M
$maxSize = 5 * 1024 * 1024;

if ($file['size'] > $maxSize)
{
	echo json_encode([
		'success' => false,
		'message' => 'Le fichier est trop volumineux!'
	]);
	exit;	
}


//Verification de type d'image
$infoImg = getimagesize($file['tmp_name']);

if ($infoImg === false)
{
	echo json_encode([
		'success' => false,
		'message' => 'Le fichier non valide!'
	]);
	exit;	
}

if ($infoImg['mime']  !== 'image/jpeg' && $infoImg['mime']  !== 'image/png')
{
	echo json_encode([
		'success' => false,
		'message' => 'Le type de fichier non autorisé!'
	]);
	exit;	
}

//Verification de overlay
$overlayAllowed = [
	'cat.png',
	'crown.png',
	'glasses.png'
];

if (!in_array($overlay, $overlayAllowed, true))
{
	echo json_encode([
		'success' => false,
		'message' => 'Overaly non autorisé!'
	]);
	exit;	
}

echo json_encode([
	'success' => true,
	'message' => 'Fichier et overlay sont bien chargé',
	'overlay' => $overlay,
	'file_size' => $file['size']
]);