<?php

header('Content-Type: application/json');

if (
	!isset($_FILES['image']) ||
	!isset($_POST['overlay']) ||
	!isset($_POST['x']) ||
	!isset($_POST['y']) ||
	!isset($_POST['width']) ||
	!isset($_POST['height'])
	)
{
	echo json_encode([
		'success' => false,
		'message' => 'Info manquants'
	]);
	exit;
}

$file = $_FILES['image'];
$overlay = $_POST['overlay'];
$x = $_POST['x'];
$y = $_POST['y'];
$width = $_POST['width'];
$height = $_POST['height'];

//Verification de parametres overlay
//Verifier est ce que on a reçu que les chiffres
if (
	filter_var($x, FILTER_VALIDATE_INT) === false ||
	filter_var($y, FILTER_VALIDATE_INT) === false ||
	filter_var($width, FILTER_VALIDATE_INT) === false ||
	filter_var($height, FILTER_VALIDATE_INT) === false
)
{
	echo json_encode([
		'success' => false,
		'message' => 'Parametres de overlay invalides.'
	]);
	exit;
}

//Convertir de string vers int
$x = (int) $x;
$y = (int) $y;
$width = (int) $width;
$height = (int) $height;


//Verifier les domensions
if (
	$x < 0 ||
	$y < 0 ||
	$width <= 0 ||
	$height <= 0 ||
	$x + $width > 600 ||
	$y + $height > 450
	
)
{
	echo json_encode([
		'success' => false,
		'message' => 'Position ou taille de overlay invalide.'
	]);
	exit;
}

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
	'glasses.png',
	'frame.png',
	'stars.png',
	'celebration.png'
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
	'file_size' => $file['size'],
	'x' => $x,
	'y' => $y,
	'width' => $width,
	'height' => $height
]);