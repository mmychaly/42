<?php

require_once __DIR__  . '/../data/database.php';

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

//On verifie que le fichier est arrivé avec un http request
if (!is_uploaded_file($file['tmp_name']))
{
	echo json_encode([
		'success' => false,
		'message' => 'Fichier uploadé invalide!'
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

//Verification de la taille réelle
$maxPixels = 20000000;

if ($infoImg[0] <= 0 || $infoImg[1] <= 0 || $infoImg[0] * $infoImg[1] > $maxPixels)
{
	echo json_encode([
		'success' => false,
		'message' => 'Les dimmensions de l\'image sont trop grandes!'
	]);
	exit;	
}

//Créer un source pour DG
//imageSourceDg est Handle interne qui pointe vers les données image chargées en mémoire par l'extension GD , type GDImage
if ($infoImg['mime'] === 'image/jpeg')
{
	$imageSourceDg = imagecreatefromjpeg($file['tmp_name']);
}
else
{
	$imageSourceDg = imagecreatefrompng($file['tmp_name']);
}
//Verification est ce que c'est bien chargé on non
if ($imageSourceDg === false)
{
	echo json_encode([
		'success' => false,
		'message' => 'Probleme avec chargement de l\'image!'
	]);
	exit;	
}

//Créer une image vide, dans laquelle on va fusionner image transformé avec overlay

$finalWidth = 600;
$finalHeight = 450;
$finalImage = imagecreatetruecolor($finalWidth, $finalHeight);//Image vide sans rien

if ($finalImage === false)
{
	echo json_encode([
		'success' => false,
		'message' => 'Impossible de  créer l\'image final!'
	]);
	exit;		
}

$imageSourceWidth = imagesx($imageSourceDg);//largeur de l'image en pixels
$imageSourceHeight = imagesy($imageSourceDg);//hauteur de l'image en pixels

$imageSourceRatio = $imageSourceWidth / $imageSourceHeight;//Ratio pour l'image source DG
$finalImageRatio = $finalWidth / $finalHeight; //Ratio pour l'image final

if ($imageSourceRatio > $finalImageRatio) //Source trop large : couper gauche/droite
{
	$cutHeight = $imageSourceHeight;//On garde hauteur
	$cutWidth = (int) round($imageSourceHeight * $finalImageRatio);//Largeur final a copier
	$sourceX = (int) round(($imageSourceWidth - $cutWidth) / 2);//Combien il faut decouper de 2 coté
	$sourceY = 0;	
}
else //image de source trop haute : couper haut/bas
{
	$cutWidth = $imageSourceWidth;//On garde largeur
	$cutHeight = (int) round($imageSourceWidth / $finalImageRatio);//Heauteur final a copier
	$sourceX = 0;
	$sourceY = (int) round(($imageSourceHeight - $cutHeight) / 2); //combien px il faut couper en bas / haut
}

//On copie les px de image source vers image final
if (!imagecopyresampled($finalImage, $imageSourceDg, 0, 0, $sourceX, $sourceY, $finalWidth, $finalHeight, $cutWidth, $cutHeight))
{
	echo json_encode([
		'success' => false,
		'message' => 'Impossible de  redimesionner l\'image !'
	]);
	exit;	
} 


//Verification de overlay , est ce que ils sont notres ou non
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

//Overaly
$overlayPath = __DIR__  . '/../../public/asset/image-def/'. $overlay;
$overlayImage = imagecreatefrompng($overlayPath);
if ($overlayImage === false)
{
	echo json_encode([
		'success' => false,
		'message' => 'Imposible de charger l\'overlay!'
	]);
	exit;	
}

$overlayFinal = imagecreatetruecolor($width, $height);
if ($overlayFinal === false)
{
	echo json_encode([
		'success' => false,
		'message' => 'Impossible de créer l\'overlay final!'
	]);
	exit;		
}

imagealphablending($overlayFinal, false);
imagesavealpha($overlayFinal, true);

$overlayWidth = imagesx($overlayImage);
$overlayHeight = imagesy($overlayImage);

if (!imagecopyresampled($overlayFinal, $overlayImage, 0, 0, 0, 0, $width, $height, $overlayWidth, $overlayHeight))
{
	echo json_encode([
		'success' => false,
		'message' => 'Impossible de  redimesionner l\'overlay !'
	]);
	exit;	
} 

//Copier l'overlay dans image final.
imagealphablending($finalImage, true);

if (!imagecopy($finalImage, $overlayFinal, $x, $y, 0, 0, $width, $height))
{
	echo json_encode([
		'success' => false,
		'message' => 'Impossible d\'ajouter l\'overlay !'
	]);
	exit;	
}

//Créer vraie l'image
$newFilename = bin2hex(random_bytes(16)) . '.png';//Créer le nom de fichier;
$uploadPath = __DIR__ . '/../../uploads/' . $newFilename; //Le chemin ou il faut enregistrer

if (!imagepng($finalImage, $uploadPath))
{
	echo json_encode([
		'success' => false,
		'message' => 'Impossible d\'enregister l\'image !'
	]);
	exit;	
}

try {
	$stmt = $pdo->prepare(
		'INSERT INTO images (user_id, filename)
		VALUES (?, ?)'
	);

	$stmt->execute([
		$_SESSION['user_id'],
		$newFilename
	]);
} catch (PDOException $e)
{
	unlink($uploadPath);
	echo json_encode([
		'success' => false,
		'message' => 'Impossible d\'enregister l\'image!'
	]);
	exit;	
}

//liberer le memoire
imagedestroy($imageSourceDg);
imagedestroy($overlayImage);
imagedestroy($overlayFinal);
imagedestroy($finalImage);

echo json_encode([
	'success' => true,
	'message' => 'Image crée avec le succès',
	'filename' => $newFilename,
	'imageUrl' => '/uploads/' . $newFilename
]);

exit;