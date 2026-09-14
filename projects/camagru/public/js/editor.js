const overlays = document.querySelectorAll('.overlay');
const captureButton = document.querySelector('#capture-button');
const displayImg = document.querySelector('#preview-overlay');

let selectedOverlay = null;

overlays.forEach((overlay) => {
	overlay.addEventListener('click', () => {

		if (overlay.classList.contains('selected')) //Si on click sur le botton deja selected on pourra désélectionné
		{
			overlay.classList.remove('selected');//on retire le class
			selectedOverlay = null;

			displayImg.src = "";
			displayImg.hidden = true;

			captureButton.disabled = true;//on desactive le botton

			return;
		}
		//pour sélectionner un overlay
		overlays.forEach((item) => {
			item.classList.remove('selected'); // on retire tout les class selected d'autres overlay
		});
		overlay.classList.add('selected');//on ajoute le class dans overlay sélectionné
		selectedOverlay = overlay.dataset.overlay;//On prends le nom de fichier
		
		captureButton.disabled = false;//on active le botton
		
		displayImg.src = `/asset/image-def/${selectedOverlay}`;//Add path of img in html element
		displayImg.hidden = false; //Toggle hidden
		
	});
});

//Add image from computer in div preview
const imageLoaded = document.querySelector('#image-load');//Element with image loaded
const previewImg = document.querySelector('#preview-image'); //Element where we display image-load
const previewText = document.querySelector('#preview-text');

imageLoaded.addEventListener('change', () => {
	const file = imageLoaded.files[0];

	if (!file)
		return;

	previewImg.src = URL.createObjectURL(file);
	previewImg.hidden = false;
	
	previewText.hidden = true;

});