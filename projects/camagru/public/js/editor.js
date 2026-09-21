

const overlays = document.querySelectorAll('.overlay');
const captureButton = document.querySelector('#capture-button');
const displayImg = document.querySelector('#preview-overlay');
const imageLoaded = document.querySelector('#image-load');//Element with image loaded
const previewImg = document.querySelector('#preview-image'); //Element where we display image-load
const previewText = document.querySelector('#preview-text');
const messageReponse = document.querySelector('#msg-capture');
const userImages = document.querySelector('#user-images');
const previewCamera = document.querySelector('#camera');
const cameraButton = document.querySelector('#button-camera');

let selectedOverlay = null;
let imageUrl = null;
let cameraStream = null;
let isSource = null;
//Positionement de overlay

const overlayParam = {
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


function updateButtonCapture() 
{
	const hasSource = isSource !== null;
	const hasOverlay = selectedOverlay !== null;

	captureButton.disabled = !(hasSource && hasOverlay)
}

function createUserImage(imageId, imageUrl)
{
	const container = document.createElement('div');
	container.classList.add('user-image');
	container.dataset.imageId = imageId;

	//creation de image
	const newImg = document.createElement('img');
	newImg.src = imageUrl;
	newImg.alt = 'Image crée';
	newImg.width = 150;

	//Creation de bouton delete
	const deleteButton = document.createElement('button');
	deleteButton.type = 'button';
	deleteButton.classList.add('delete-image');
	deleteButton.textContent='Supprimer';

	container.append(newImg, deleteButton);

	return container;
}

function captureImage()
{
	const canvas = document.createElement('canvas');

	canvas.width = 600;
	canvas.height = 450;

	const context = canvas.getContext('2d');

	context.drawImage(previewCamera, 0,0,600,450);

	return new Promise((resolve) => {
		canvas.toBlob((blob) => {
			resolve(blob); 
		}, 'image/png');
	});
}

overlays.forEach((overlay) => {
	overlay.addEventListener('click', () => {

		if (overlay.classList.contains('selected')) //Si on click sur le botton deja selected on pourra désélectionné
		{
			overlay.classList.remove('selected');//on retire le class
			selectedOverlay = null;

			displayImg.src = "";
			displayImg.hidden = true;

			updateButtonCapture();

			return;
		}
		//pour sélectionner un overlay
		overlays.forEach((item) => {
			item.classList.remove('selected'); // on retire tout les class selected d'autres overlay
		});
		overlay.classList.add('selected');//on ajoute le class dans overlay sélectionné
		selectedOverlay = overlay.dataset.overlay;//On prends le nom de fichier		
		const params =overlayParam[selectedOverlay];
		displayImg.src = `/asset/image-def/${selectedOverlay}`;//Add path of img in html element
		displayImg.hidden = false; //Toggle hidden
		displayImg.style.left = `${params.x}px`;
		displayImg.style.top = `${params.y}px`;
		displayImg.style.width = `${params.width}px`;
		displayImg.style.height = `${params.height}px`;
		previewText.hidden = true;
		updateButtonCapture();
	});
});

//Add image from computer in div preview



imageLoaded.addEventListener('change', () => {
	const file = imageLoaded.files[0];

	if (!file)
		return;

	if (cameraStream)
	{
		cameraStream.getTracks().forEach((track) => {
			track.stop();
		});

		cameraStream = null;
		previewCamera.srcObject = null;
		previewCamera.hidden = true;
	}

	isSource = 'upload';


	if (imageUrl)
		URL.revokeObjectURL(imageUrl);

	imageUrl = URL.createObjectURL(file);
	previewImg.src = imageUrl;
	previewImg.hidden = false;
	previewText.hidden = true;

	updateButtonCapture();

});

captureButton.addEventListener('click', async () => {
	let file = null;

	if (!selectedOverlay)
		return;

	//const file = imageLoaded.files[0];

	if (isSource === "upload")
	{
		file = imageLoaded.files[0];

		if (!file)
			return;
	}
	else if (isSource === "camera")
	{
		file = await captureImage();

		if (!file)
		{
			messageReponse.textContent = "Imposible de prendre la photo."
			return;
		}
	}
	else 
		return;


	const maxSize = 5 * 1024 * 1024;

	if (file.size > maxSize)
	{
		messageReponse.textContent = "La taille de l'image est trop grande, max 5 Mo";
		return;
	}


	const formData = new FormData();
	const param = overlayParam[selectedOverlay];

	formData.append('image', file);
	formData.append('overlay', selectedOverlay);
	formData.append('x', param.x);
	formData.append('y', param.y);
	formData.append('width', param.width);
	formData.append('height', param.height);

	try {
		const res = await fetch('/image/create', {
			method: 'POST',
			body: formData
		});

		if (!res.ok)
		{
			messageReponse.textContent = 'Erreur pendant l\'envoi de l\'image';
			return;
		}

		const data = await res.json();
		
		messageReponse.textContent = data.message;

		if (data.success)
		{
			const noImgMessage = document.querySelector('#no-img-message');
			
			if (noImgMessage)
				noImgMessage.remove();

			const container = createUserImage(data.imageId, data.imageUrl);
			userImages.prepend(container);

			const totalImgs = userImages.querySelectorAll('.user-image');

			if (totalImgs.length > 5)
				totalImgs[totalImgs.length - 1].remove();
		}
	}
	catch{
		messageReponse.textContent = 'Serveur ne reponde pas!';
	}

});

//Si user click sur le bouton supprimer
userImages.addEventListener('click', async (event) => {
	if (!event.target.classList.contains('delete-image'))
		return;
	
	const parentDiv = event.target.closest('.user-image');//On trouver le parent de bouton, dans ce parent nous avons id de l'image
	const imageId = parentDiv.dataset.imageId;

	const formData = new FormData();//On ajout information sur id de l'image 
	formData.append('image_id', imageId);

	//On fait request pour supprimer l'image 
	try{
		const res = await fetch("/image/delete", {
			method: "POST",
			body: formData
		});

		if (!res.ok)
		{
			messageReponse.textContent = "Erreur de suppression."
			return;
		}

		const data = await res.json();
		messageReponse.textContent = data.message;//On afficher le message

		if (data.success)
		{
			parentDiv.remove();//On retire div avec l'image et bouton

			if (data.displayImage)//Puis si dans db nous avons + que 4 images on va afficher 5eme 
			{
				const container = createUserImage(data.displayImage.id, data.displayImage.imageUrl);
				userImages.append(container);
			}

			if (userImages.querySelectorAll('.user-image').length === 0)//Si on a supprimé tout les images on affiche que il n'a plus de images
			{
				const message = document.createElement('p');
				message.id = 'no-img-message';
				message.textContent = 'Aucune image.';
				userImages.append(message);
			}
		}
	}catch {
		messageReponse.textContent = 'Serveur ne répond pas!';
	}

});


//Fonctionement de camera
cameraButton.addEventListener('click', async () => {
	try{
		cameraStream = await navigator.mediaDevices.getUserMedia({video: true, audio: false});
		previewCamera.srcObject = cameraStream;
		isSource = 'camera';

		previewCamera.hidden = false;
		previewImg.hidden = true;
		previewText.hidden = true;

		updateButtonCapture();
	}
	catch {
		messageReponse.textContent = 'Impossible acceder a la camera.';
	}

});