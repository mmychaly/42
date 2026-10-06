var overlays = document.querySelectorAll('.overlay[data-overlay]');
var noStickerButton = document.querySelector('#no-sticker-button');
var captureButton = document.querySelector('#capture-button');
var previewOverlays = document.querySelector('#preview-overlays');
var imageLoaded = document.querySelector('#image-load');//Element with image loaded
var previewImg = document.querySelector('#preview-image'); //Element where we display image-load
var previewText = document.querySelector('#preview-text');
var messageReponse = document.querySelector('#msg-capture');
var userImages = document.querySelector('#user-images');
var previewCamera = document.querySelector('#camera');
var cameraButton = document.querySelector('#button-camera');
var preview = document.querySelector('#preview');
var tokenCsrf = document.getElementById('csrf-token').value;

var selectedOverlays = [];
var noStickerSelect = false;

var imageUrl = null;
var cameraStream = null;
var cameraRequest = 0;
var cameraObjectUrl = null;
var isSource = null;
//Positionement de overlay

var overlayParam = {
	'cat.png': {
		x: 150,
		y: 300,
		width: 200,
		height: 150
	},
	'glasses.png': {
		x: 200,
		y: 170,
		width: 200,
		height: 120
	},
	'frame.png': {
		x: 0,
		y: 0,
		width: 600,
		height: 450		
	},
	'stars.png': {
		x: 0,
		y: 0,
		width: 600,
		height: 450		
	},
	'celebration.png': {
		x: 0,
		y: 0,
		width: 600,
		height: 450		
	}
}

function requestUserMedia(data)
{
	//Pour les navigateurs recents
	if (navigator.mediaDevices && typeof navigator.mediaDevices.getUserMedia === 'function')
		return navigator.mediaDevices.getUserMedia(data);

	//Pour les navigateurs anciens
	var toolGetUserMedia = 
		navigator.getUserMedia ||
		navigator.webkitGetUserMedia ||
		navigator.mozGetUserMedia;

	if (!toolGetUserMedia)
		return Promise.reject(new Error('GetUserMedia ne fonctionne pas'));

	return new Promise(function (resolve, reject) {
		toolGetUserMedia.call(navigator, data, resolve, reject);
	});
}

function timeoutUserMedia(data, timeout)
{
	return new Promise(function (resolve, reject) {
		var isFinished = false;

		var timer = setTimeout(function () {
			if (isFinished)
				return;

			isFinished = true;

			reject(new Error('CameraPermissionTimeout'));
		}, timeout);

		requestUserMedia(data)
		.then(function (stream) {
			if (isFinished)
			{
				stopStream(stream);
				return;
			}

			isFinished = true;
			clearTimeout(timer);

			resolve(stream);
		})
		.catch(function (error) {
			if (isFinished)
				return;

			isFinished = true;
			clearTimeout(timer);
			reject (error);                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                         (error);
		});
	});
}

function joinCameraStream(stream)
{
	//Navigateurs modernes
	if ('srcObject' in previewCamera)
	{
		previewCamera.srcObject = stream;
		return;
	}

	//Anciennes versions de firefox
	if ('mozSrcObject' in previewCamera)
	{
		previewCamera.mozSrcObject = stream;
		return;
	}

	//Anciennes versions de Chrome
	var urlObject = window.URL ||window.webkitURL;
	if (urlObject && typeof urlObject.createObjectURL === 'function')
	{
		cameraObjectUrl = urlObject.createObjectURL(stream);
		previewCamera.src = cameraObjectUrl;
	}
}

function cameraSource()
{
	if ('srcObject' in previewCamera)
	{
		previewCamera.srcObject = null;
		return;
	}

	if ('mozSrcObject' in previewCamera)
		previewCamera.mozSrcObject = null;

	if (cameraObjectUrl)
	{
		var urlObject = window.URL || window.webkitURL;

		if (urlObject && typeof urlObject.revokeObjectURL === 'function')
			urlObject.revokeObjectURL(cameraObjectUrl);
		
		cameraObjectUrl = null;
	}

	previewCamera.removeAttribute('src');
}

function stopStream(stream)
{
	if (!stream)
		return;

	var tracks = stream.getTracks();

	for (var i = 0; i < tracks.length; i++)
		tracks[i].stop();
}

function stopCamera()
{
	if (cameraStream)
	{
		stopStream(cameraStream);
		cameraStream = null;
	}

	previewCamera.pause();
	cameraSource();
	previewCamera.hidden = true;
}

window.addEventListener('pagehide', function () {
	cameraRequest++;
	stopCamera();
	isSource = null;
});

function updateOverlayDisplay()
{
	while (previewOverlays.firstChild)
		previewOverlays.removeChild(previewOverlays.firstChild);

	var scale = preview.clientWidth / 600;

	for (var i =0; i < selectedOverlays.length; i++)
	{
		var overlayName = selectedOverlays[i];
		var params = overlayParam[overlayName];

		var img = document.createElement('img');
		img.src = '/asset/image-def/' + overlayName;
		img.alt = 'Overlay';
		img.classList.add('preview-sticker');

		img.style.left = (params.x * scale) + 'px';
		img.style.top = (params.y * scale) + 'px';
		img.style.width = (params.width * scale) + 'px';
		img.style.height = (params.height * scale) + 'px';

		previewOverlays.appendChild(img);
	}
}

function updateButtonCapture() 
{
	var hasSource = isSource !== null;
	var isChoseOverlay = noStickerSelect || selectedOverlays.length > 0;

	captureButton.disabled = !(hasSource && isChoseOverlay);
}

function createUserImage(imageId, imageUrl)
{
	var container = document.createElement('div');

	container.classList.add('user-image');
	container.dataset.imageId = imageId;

	//creation de image
	var newImg = document.createElement('img');

	newImg.src = imageUrl;
	newImg.alt = 'Image crée';
	newImg.width = 150;

	//Creation de bouton delete
	var deleteButton = document.createElement('button');
	deleteButton.type = 'button';
	deleteButton.classList.add('delete-image');
	deleteButton.textContent='Supprimer';

	container.appendChild(newImg);
	container.appendChild(deleteButton);

	return container;
}

function dataUrlBlob(dataUrl)
{
	var part = dataUrl.split(',');
	var binary = atob(part[1]);
	var len = binary.length;
	var bytes = new Uint8Array(len);

	for (var i = 0; i < len; i++)
		bytes[i] = binary.charCodeAt(i);

	return new Blob(
		[bytes],
		{ type: 'image/png'}
	);
}

function captureImage()
{
	if (!cameraStream || 
		previewCamera.readyState < 2 ||
		previewCamera.videoWidth === 0 ||
		previewCamera.videoHeight === 0)
	{
		return Promise.resolve(null);
	}

	var videoTrack = cameraStream.getVideoTracks();
	var isLiveTrack = false;

	for (var i = 0; i < videoTrack.length; i++)
	{
		if (videoTrack[i].readyState === 'live')
		{
			isLiveTrack = true;
			break;
		}
	}

	if (!isLiveTrack)
		return Promise.resolve(null);

	var canvas = document.createElement('canvas');

	canvas.width = 600;
	canvas.height = 450;

	var context = canvas.getContext('2d');

	if (!context)
		return Promise.resolve(null);

	try {
		context.drawImage(previewCamera, 0, 0, 600, 450);
	} catch (error)
	{
		return Promise.resolve(null);
	}

	return new Promise(function (resolve)  {
		
		//Methode pour les navigateurs récents
		if (typeof canvas.toBlob === 'function')
		{
			canvas.toBlob(function (blob) {
				resolve(blob); 
			}, 'image/png');

			return;
		}

		//Pour les navigateurs anciens
		try {
			var dataUrl = canvas.toDataURL('image/png');
			resolve(dataUrlBlob(dataUrl));
		}
		catch (error)
		{
			resolve(null);
		}
	});
}

window.addEventListener('resize', updateOverlayDisplay);

function eventOverlay(overlay)
{
	overlay.addEventListener('click', function () {
		
		var overlayName = overlay.dataset.overlay;

		if (overlay.classList.contains('selected')) //Si on click sur le botton deja selected on pourra désélectionné
		{
			overlay.classList.remove('selected');//on retire le class

			for (var i = 0; i < selectedOverlays.length; i++)
			{
				if (selectedOverlays[i] === overlayName)
				{
					selectedOverlays.splice(i, 1);
					break;
				}
			}
		}
		else
		{
			overlay.classList.add('selected');
			selectedOverlays.push(overlayName);

			noStickerSelect = false;
			noStickerButton.classList.remove('selected');
		}

		updateOverlayDisplay();
		updateButtonCapture();
	});
}

for (var i = 0; i < overlays.length; i++)
	eventOverlay(overlays[i]);

noStickerButton.addEventListener('click', function () {
	noStickerSelect = !noStickerSelect;

	if (noStickerSelect)
	{
		noStickerButton.classList.add('selected');

		selectedOverlays = [];

		for (var i = 0; i < overlays.length; i++)
			overlays[i].classList.remove('selected');
	}
	else
		noStickerButton.classList.remove('selected');

	updateOverlayDisplay();
	updateButtonCapture();
});


//Add image from computer in div preview
imageLoaded.addEventListener('change', function () {
	var file = imageLoaded.files[0];
	var urlObject = window.URL || window.webkitURL;

	if (!file)
		return;

	cameraRequest++;
	stopCamera();
	cameraButton.disabled = false;

	isSource = 'upload';


	if (imageUrl && urlObject && typeof urlObject.revokeObjectURL === 'function')
		urlObject.revokeObjectURL(imageUrl);

	if (urlObject && typeof urlObject.createObjectURL === 'function')
	{
		imageUrl = urlObject.createObjectURL(file);
		previewImg.src = imageUrl;
	}

	previewImg.hidden = false;
	previewText.hidden = true;

	updateButtonCapture();

});

function sendImage(file)
{
	if (!file)
		return;

	var maxSize = 5 * 1024 * 1024;

	if (file.size > maxSize)
	{
		messageReponse.textContent = "La taille de l'image est trop grande, max 5 Mo";
		return;
	}

	var formData = new FormData();
	
	formData.append('image', file);
	formData.append('no_sticker', noStickerSelect ? '1' : '0');

	for (var i = 0; i < selectedOverlays.length; i++)
	{
		formData.append(
			'overlays[]',
			selectedOverlays[i]
		);
	}

	formData.append('csrf_token', tokenCsrf);

	fetch('/image/create', {
			method: 'POST',
			credentials: 'same-origin',
			body: formData
	})
	.then(function (res) {
		
		if (!res.ok)
		{
			messageReponse.textContent = "Erreur pendant l'envoi de l'image";
			return null;
		}

		return res.json();
	})
	.then(function (data) {

		if (data == null)
			return;
		
		messageReponse.textContent = data.message;

		if (!data.success)
			return;

		var noImgMessage = document.querySelector('#no-img-message');
			
		if (noImgMessage && noImgMessage.parentNode)
				noImgMessage.parentNode.removeChild(noImgMessage);

		var container = createUserImage(data.imageId, data.imageUrl);

		if (userImages.firstChild)
			userImages.insertBefore(container, userImages.firstChild);
		else
			userImages.appendChild(container);

		
	})
	.catch(function () {
		messageReponse.textContent = 'Serveur ne reponde pas!';
	});
}

captureButton.addEventListener('click', function () {

	if (!noStickerSelect && selectedOverlays.length === 0)
		return;

	if (isSource === "upload")
	{
		var file = imageLoaded.files[0];

		if (!file)
			return;

		sendImage(file);
		return;
	}

	if (isSource === "camera")
	{
		if (previewCamera.readyState < 2)
		{
			messageReponse.textContent = "Caméra se prépare, réessayez plutard!";
			return;
		}

		captureImage()
		.then(function (file) {
			if (!file)
			{
				messageReponse.textContent = "Imposible de prendre la photo.";
				return;
			}
			sendImage(file);
		})
		.catch(function () {
			messageReponse.textContent = "Imposible de prendre la photo.";
		});
	}
});

//Si user click sur le bouton supprimer
userImages.addEventListener('click', function (event) {

	if (!event.target.classList.contains('delete-image'))
		return;
	
	var parentDiv = event.target.closest('.user-image');//On trouver le parent de bouton, dans ce parent nous avons id de l'image
	if (!parentDiv)
		return;

	var imageId = parentDiv.dataset.imageId;

	var formData = new FormData();//On ajout information sur id de l'image 
	formData.append('image_id', imageId);
	formData.append('csrf_token', tokenCsrf);

	//On fait request pour supprimer l'image 
	fetch("/image/delete", {
		method: "POST",
		credentials: 'same-origin',
		body: formData
	})
	.then(function (res) {
		if (!res.ok)
		{
			messageReponse.textContent = "Erreur de suppression."
			return null;
		}

		return res.json();
	})
	.then(function (data) {
		if (data === null)
			return;

		messageReponse.textContent = data.message;//On afficher le message

		if (!data.success)
			return;

		if (parentDiv.parentNode)
			parentDiv.parentNode.removeChild(parentDiv);//On retire div avec l'image et bouton
	
		if (userImages.querySelectorAll('.user-image').length === 0)//Si on a supprimé tout les images on affiche que il n'a plus de images
		{
			var message = document.createElement('p');
			message.id = 'no-img-message';
			message.textContent = 'Aucune image.';
			userImages.appendChild(message);
		}
	})
	.catch (function () {
		messageReponse.textContent = 'Serveur ne répond pas!';
	});
});

function waitCamera(request)
{
	return new Promise(function (resolve, reject) {
		var startTime = Date.now();

		function checkCamera()
		{
			if (request !== cameraRequest)
			{
				resolve(false);
				return;
			}

			if (previewCamera.readyState >= 2 &&
				previewCamera.videoWidth > 0 &&
				previewCamera.videoHeight > 0)
			{
				resolve(true);
				return;
			}

			if (Date.now() - startTime >= 8000)
			{
				reject(new Error('CameraTimeout'));
				return;
			}

			setTimeout(checkCamera, 100);
		}

		checkCamera();
	});
}

function addTrackEnded(track, request)
{
	track.addEventListener('ended', function () {
		if (request !== cameraRequest)
			return;

		cameraRequest++;

		stopCamera();

		isSource = null;

		previewText.textContent = "Caméra déconnectée";
		previewText.hidden = false;

		updateButtonCapture();

		cameraButton.disabled = false;
	});
}


//Fonctionement de camera
cameraButton.addEventListener('click', function () {
	
	var request = ++cameraRequest;

	cameraButton.disabled = true;

	stopCamera();
	isSource = null;
	updateButtonCapture();

	messageReponse.textContent = '';
	previewImg.hidden = true;
	previewText.textContent = 'Demarrage de camera...';
	previewText.hidden = false;

	timeoutUserMedia({
		video: true,
		audio: false
	}, 10000)
	.then(function (stream) {
		if (request !== cameraRequest)
		{
			stopStream(stream);
			return null;
		}

		cameraStream = stream;
		var tracks = stream.getVideoTracks();
		for (var i = 0; i < tracks.length; i++)
			addTrackEnded(tracks[i], request);

		joinCameraStream(stream);

		previewCamera.hidden = false;

		try
		{
			var resPlay = previewCamera.play();

			if (resPlay && typeof resPlay.catch === 'function')
			{
				resPlay.catch(function () {});
			}
		}
		catch (error)
		{

		}

		return waitCamera(request);
	})
	.then(function (cameraReady) {
		if (cameraReady === null || cameraReady === false)
			return;

		if (request !== cameraRequest)
			return;

		isSource = 'camera';
		previewImg.hidden = true;
		previewText.hidden = true;

		imageLoaded.value = '';

		updateButtonCapture();
	})
	.catch(function (error) {
		if (request !== cameraRequest)
			return;

		stopCamera();
		isSource = null;

		previewText.textContent = "Aucune image disponible";
		previewText.hidden = false;

		if (error && error.message === 'CameraPermissionTimeout')
		{
			messageReponse.textContent = "La demande à la caméra a expiré"
		}
		else if (error && (error.name === 'NotAllowedError' || 
					error.name === 'PermissionDeniedError' || 
					error.name === 'SecurityError'))
		{
			messageReponse.textContent = 'Autorisez la caméra dans le navigateur et réessayez!';
		}
		else if (error && (error.name === 'NotReadableError' || error.name === 'TrackStartError'))
		{
			messageReponse.textContent = 'Caméra occupée ou indisponible!';
		}
		else
		{
			messageReponse.textContent = 'Impossible de démarrer la caméra.Réessayez!';
		}
			
		updateButtonCapture();
	})
	.then(function () {
		if (request === cameraRequest)
			cameraButton.disabled = false;
	});
});

