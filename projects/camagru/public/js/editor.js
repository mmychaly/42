

const overlays = document.querySelectorAll('.overlay');
const captureButton = document.querySelector('#capture-button');
const displayImg = document.querySelector('#preview-overlay');
const imageLoaded = document.querySelector('#image-load');//Element with image loaded
const previewImg = document.querySelector('#preview-image'); //Element where we display image-load
const previewText = document.querySelector('#preview-text');
const messageReponse = document.querySelector('#msg-capture');

let selectedOverlay = null;
let imageUrl = null;

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
	const hasImg = imageUrl !== null;
	const hasOverlay = selectedOverlay !== null;

	captureButton.disabled = !(hasImg && hasOverlay)
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
	if (imageUrl)
		URL.revokeObjectURL(imageUrl);

	imageUrl = URL.createObjectURL(file);
	previewImg.src = imageUrl;
	previewImg.hidden = false;
	previewText.hidden = true;

	updateButtonCapture();

});

captureButton.addEventListener('click', async () => {
	const file = imageLoaded.files[0];

	if (!file || !selectedOverlay)
		return;

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
			const userImgs = document.querySelector('#user-images');
			const noImgMessage = document.querySelector('#no-img-message');
			
			if (noImgMessage)
				noImgMessage.remove();
			
			const newImg = document.createElement('img');

			newImg.src = data.imageUrl;
			newImg.width = 150;

			userImgs.prepend(newImg);

			const totalImgs = userImgs.querySelectorAll('img');

			if (totalImgs.length > 5)
				totalImgs[totalImgs.length - 1].remove();
		}
	}
	catch {
		messageReponse.textContent = 'Serveur ne reponde pas!';
	}

});

