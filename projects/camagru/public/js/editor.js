

const overlays = document.querySelectorAll('.overlay');
const captureButton = document.querySelector('#capture-button');
const displayImg = document.querySelector('#preview-overlay');
const imageLoaded = document.querySelector('#image-load');//Element with image loaded
const previewImg = document.querySelector('#preview-image'); //Element where we display image-load
const previewText = document.querySelector('#preview-text');

let selectedOverlay = null;
let imageUrl = null;

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
		displayImg.src = `/asset/image-def/${selectedOverlay}`;//Add path of img in html element
		displayImg.hidden = false; //Toggle hidden
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

	formData.append('image', file);
	formData.append('overlay', selectedOverlay);

	const res = await fetch('/image/create', {
		method: 'POST',
		body: formData
	});

	const data = await res.json();

	console.log(data);
});
