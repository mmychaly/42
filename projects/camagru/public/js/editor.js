const overlays = document.querySelectorAll('.overlay');
const captureButton = document.querySelector('#capture-button');

let selectedOverlay = null;

overlays.forEach((overlay) => {
	overlay.addEventListener('click', () => {

		if (overlay.classList.contains('selected')) //Si on click sur le botton deja selected on pourra désélectionné
		{
			overlay.classList.remove('selected');//on retire le class
			selectedOverlay = null;
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

		console.log(selectedOverlay);//retirer plutard
	});
});