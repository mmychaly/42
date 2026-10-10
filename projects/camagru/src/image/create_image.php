<?php

require_once __DIR__  . '/../data/database.php';

header('Content-Type: application/json');

if ( !isset(
		$_FILES['image']['error'],
		$_FILES['image']['size'],
		$_FILES['image']['tmp_name']
    ) ||
	!is_int($_FILES['image']['error']) ||
	!is_int($_FILES['image']['size']) ||
	!is_string($_FILES['image']['tmp_name'])
	)
{
	echo json_encode([
		'success' => false,
		'message' => 'Info manquants ou invalides'
	]);
	exit;
}

$file = $_FILES['image'];
$noOverlay = ($_POST['no_sticker'] ?? '0') === '1';
$overlays = $_POST['overlays'] ?? [];

if(!is_array($overlays))
{
	echo json_encode([
		'success' => false,
		'message' => 'Liste de overlay invalide.'
	]);
	exit;
}

if ($noOverlay && !empty($overlays))
{
	echo json_encode([
		'success' => false,
		'message' => 'Choix de overlay invalide.'
	]);
	exit;
}

if (!$noOverlay && empty($overlays))
{
	echo json_encode([
		'success' => false,
		'message' => 'Aucun overlay choisis.'
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

// Reject files larger than 5 MB.
$maxSize = 5 * 1024 * 1024;

if ($file['size'] > $maxSize)
{
	echo json_encode([
		'success' => false,
		'message' => 'Le fichier est trop volumineux!'
	]);
	exit;	
}

// Check that the file was uploaded through an HTTP request.
if (!is_uploaded_file($file['tmp_name']))
{
	echo json_encode([
		'success' => false,
		'message' => 'Fichier uploadé invalide!'
	]);
	exit;	
}


// Check the image type.
$infoImg = @getimagesize($file['tmp_name']);

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

// Check the actual image dimensions.
$maxPixels = 16000000;

if ($infoImg[0] <= 0 || $infoImg[1] <= 0 || $infoImg[0] * $infoImg[1] > $maxPixels)
{
	echo json_encode([
		'success' => false,
		'message' => 'Les dimmensions de l\'image sont trop grandes!'
	]);
	exit;	
}

// Create a GD image source.
// imageSourceDg is a GDImage object containing the image data loaded into memory by the GD extension.
if ($infoImg['mime'] === 'image/jpeg')
{
	$imageSourceDg = @imagecreatefromjpeg($file['tmp_name']);
}
else
{
	$imageSourceDg = @imagecreatefrompng($file['tmp_name']);
}

// Check that the image was loaded successfully.
if ($imageSourceDg === false)
{
	echo json_encode([
		'success' => false,
		'message' => 'Probleme avec chargement de l\'image!'
	]);
	exit;	
}


$overlayParam = [
	'cat.png' => [
		'x' => 150,
		'y' => 300,
		'width' => 200,
		'height' => 150
	],
	'glasses.png' => [
		'x' => 200,
		'y' => 170,
		'width' => 200,
		'height' => 120
	],
	'frame.png' => [
		'x' => 0,
		'y' => 0,
		'width' => 600,
		'height' => 450
	],
	'stars.png' => [
		'x' => 0,
		'y' => 0,
		'width' => 600,
		'height' => 450
	],
	'celebration.png' => [
		'x' => 0,
		'y' => 0,
		'width' => 600,
		'height' => 450
	]
];

// Create an empty final image where the resized source image and overlays will be merged.

$finalWidth = 600;
$finalHeight = 450;
$finalImage = imagecreatetruecolor($finalWidth, $finalHeight);// Create an empty image.

if ($finalImage === false)
{
	echo json_encode([
		'success' => false,
		'message' => 'Impossible de  créer l\'image final!'
	]);
	exit;		
}

$imageSourceWidth = imagesx($imageSourceDg);// Source image width in pixels.
$imageSourceHeight = imagesy($imageSourceDg);// Source image height in pixels.

$imageSourceRatio = $imageSourceWidth / $imageSourceHeight;// Aspect ratio of the source GD image.
$finalImageRatio = $finalWidth / $finalHeight; // Aspect ratio of the final image.

if ($imageSourceRatio > $finalImageRatio) // Source image is too wide: crop the left and right sides.
{
	$cutHeight = $imageSourceHeight;// Keep the full source height.
	$cutWidth = (int) round($imageSourceHeight * $finalImageRatio);// Calculate the source width to copy.
	$sourceX = (int) round(($imageSourceWidth - $cutWidth) / 2);// Calculate how many pixels to crop equally from both sides.
	$sourceY = 0;	
}
else // Source image is too tall: crop the top and bottom.
{
	$cutWidth = $imageSourceWidth;// Keep the full source width.
	$cutHeight = (int) round($imageSourceWidth / $finalImageRatio);// Calculate the source height to copy.
	$sourceX = 0;
	$sourceY = (int) round(($imageSourceHeight - $cutHeight) / 2); // Calculate how many pixels to crop equally from the top and bottom.
}

// Resize and copy the source image into the final image.
if (!imagecopyresampled(
	$finalImage,
	$imageSourceDg,
	0,
	0,
	$sourceX,
	$sourceY,
	$finalWidth,
	$finalHeight,
	$cutWidth,
	$cutHeight
))
{
	echo json_encode([
		'success' => false,
		'message' => 'Impossible de  redimesionner l\'image !'
	]);
	exit;	
} 

foreach ($overlays as $overlay)
{
	if (!is_string($overlay) || !isset($overlayParam[$overlay]))
	{
		echo json_encode([
			'success' => false,
			'message' => 'Overlay non valide!'
		]);
		exit;	
	}

	$params = $overlayParam[$overlay];

	$x = $params['x'];
	$y= $params['y'];
	$width = $params['width'];
	$height = $params['height'];

	$overlayPath = __DIR__  . '/../../public/asset/image-def/'. $overlay;
	$overlayImage = @imagecreatefrompng($overlayPath);
	
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

	if (!imagecopyresampled(
		$overlayFinal,
		$overlayImage,
		0,
		0,
		0,
		0,
		$width,
		$height,
		$overlayWidth,
		$overlayHeight
	))
	{
		echo json_encode([
			'success' => false,
			'message' => 'Impossible de  redimesionner l\'overlay !'
		]);
		exit;	
	} 

	imagealphablending($finalImage, true);

	if (!imagecopy(
		$finalImage,
		$overlayFinal,
		$x,
		$y,
		0,
		0,
		$width,
		$height
	))
	{
		echo json_encode([
			'success' => false,
			'message' => 'Impossible d\'ajouter l\'overlay !'
		]);
		exit;	
	}

	imagedestroy($overlayImage);
	imagedestroy($overlayFinal);
}

// Create and save the final image.
$newFilename = bin2hex(random_bytes(16)) . '.png';// Create a random filename.
$uploadPath = __DIR__ . '/../../uploads/' . $newFilename; // Path where the image will be saved.

if (!@imagepng($finalImage, $uploadPath))
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

	$imageId = (int) $pdo->lastInsertId();
}
catch (PDOException $e)
{
	@unlink($uploadPath);

	echo json_encode([
		'success' => false,
		'message' => 'Impossible d\'enregister l\'image!'
	]);

	exit;	
}

// Free the GD image resources.
imagedestroy($imageSourceDg);
imagedestroy($finalImage);

echo json_encode([
	'success' => true,
	'message' => 'Image crée avec le succès',
	'filename' => $newFilename,
	'imageUrl' => '/uploads/' . $newFilename,
	'imageId' => $imageId
]);

exit;