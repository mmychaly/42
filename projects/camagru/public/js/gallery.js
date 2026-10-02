var likeButton = document.querySelectorAll('.like-button');
var commentButton = document.querySelectorAll('.button-comment');
var cancelCommentButton = document.querySelectorAll('.cancel-comment');
var commentForm = document.querySelectorAll('.form-comment');

var elementCsrf = document.getElementById('csrf-token');
var tokenCsrf = elementCsrf ? elementCsrf.value : '';

//Ici on rassemble les commentaires
//Le conteneur div va contenir:
//ligne 1 == crée par username
//ligne 2 == message
//ligne 3 == date de création
function createComment(comment)
{
	var container = document.createElement('div');
	container.classList.add('comment');

	var text = document.createElement('p');

	var username = document.createElement('strong');
	username.textContent = comment.username;

	var message = document.createTextNode(' : ' + comment.message);

	text.appendChild(username);
	text.appendChild(message);

	var date = document.createElement('small');
	date.textContent = comment.createdAt;

	container.appendChild(text);
	container.appendChild(date);

	return container;
}
//Fonction pour ajouter un événement au bouton qui affiche le champ de commentaire
function eventCommentButton(button)
{
	button.addEventListener('click', function () {

		var article = button.closest('.gallery-image');//On regarde dans quel article/image il y a eu un click
		var form = article.querySelector('.form-comment');//On trouve le form de cette image

		form.hidden = false;//form devient visible
		button.hidden = true;//Bouton dispares
	});
}
//On ajoute eventCommentButton à chaque bouton qui affiche le champ de commentaire
for (var i = 0; i < commentButton.length; i++)
{
	eventCommentButton(commentButton[i]);
}

//Fonction qui ajoute un event pour le bouton qui annule le commentaire

function eventCancelCommentButton(button)
{
	button.addEventListener('click', function () {
		var article = button.closest('.gallery-image');
		var form = article.querySelector('.form-comment');
		var showCommentButton = article.querySelector('.button-comment');
		var inputComment = form.querySelector('.comment-input');
		var errorMessage = form.querySelector('.msg-error-comment');

		inputComment.value = '';//on supprime le contenu de input

		errorMessage.textContent = '';//Si il y a eu une erreur on supprime le contenu 
		errorMessage.hidden = true; //Le champ d'erreur invisible

		form.hidden = true;//Le champ input de form invisible

		showCommentButton.hidden = false;//Bouton pour ajouter commantaire devient visible
	});
}

//On ajoute cancelCommentButton à chaque bouton qui annule le commentaire
for (var i = 0; i < cancelCommentButton.length; i++)
{
	eventCancelCommentButton(cancelCommentButton[i]);
}

cancelCommentButton.forEach((button) => {
	button.addEventListener('click', () => {


		inputCans.value = "";//on supprime le contenu de input
		
		errorMessage.textContent = '';
		errorMessage.hidden = true;
		form.hidden = true;//on cache le input de form
		commentButton.hidden = false;//Bouton pour ajouter commantaire devient visible
	});
});

likeButton.forEach((button) => {
	button.addEventListener('click', async () => {
			
			var article = button.closest('.gallery-image');
			var errorMessage = article.querySelector('.error-massage');
			var likeNumber = article.querySelector('.like-number');

			var formData = new FormData();
			var imageId = button.dataset.imageId;
			formData.append('image_id', imageId);
			formData.append('csrf_token', tokenCsrf);

			try {
				button.disabled = true;

				var res = await fetch("/image/like", {
					method: "POST",
					body: formData
				});

				if (!res.ok)
				{
					errorMessage.textContent = "Une erreur est survenue!";
					errorMessage.hidden = false;
					return;
				}

			
				var data = await res.json();
				

				if (data.success)
				{
					likeNumber.textContent = data.likeNumber;

					if (data.like)
						button.textContent = 'Retirer le like';
					else
						button.textContent = 'Like';

					errorMessage.textContent = '';
					errorMessage.hidden = true;
				}
				else
				{
					errorMessage.textContent = data.message;
					errorMessage.hidden = false;
				}

			} catch 
			{
				errorMessage.textContent = "Erreur est survenue!";
				errorMessage.hidden = false;
			}
			finally{
				button.disabled = false;
			}
	});
});

//Commentaires
//On insltale event listener pour chaque form. On lance si bouton submit a cliqué
commentForm.forEach((form) => {
	form.addEventListener('submit', async (event) => {
		event.preventDefault();//On 

		var imageId = form.dataset.imageId;
		var input = form.querySelector('.comment-input');
		var message = input.value.trim();

		var erroMessage = form.querySelector('.msg-error-comment');

		if (!message)
		{
			erroMessage.textContent = 'Le commentaire ne doit pas etre vide!';
			erroMessage.hidden = false;
			return;
		}

			var formData = new FormData();
			formData.append('image_id', imageId);
			formData.append('message', message);
			formData.append('csrf_token', tokenCsrf);

		var submitButton = form.querySelector('button[type="submit"]');

		submitButton.disabled = true;//on a besoin de desactive le bouton de submit de formulare pour n'est pas pouvoir envoier plusieurs

			try {
				var res = await fetch("/image/comment", {
					method: "POST",
					body: formData
				});

				if (!res.ok)
				{
					erroMessage.textContent = "Une erreur est survenue!";
					erroMessage.hidden = false;
					return;
				}

			
				var data = await res.json();
				

				if (!data.success)
				{
					erroMessage.textContent = data.message;
					erroMessage.hidden = false;
					return;
				}

				var parentComment = form.closest('.comments');
				var comment = createComment(data.comment);
				var showButton = form.closest('.comments').querySelector('.button-comment');

				parentComment.insertBefore(comment, showButton);

				input.value = "";
				erroMessage.textContent = '';
				erroMessage.hidden = true;

				form.hidden = true;

				
				showButton.hidden = false;

			} catch 
			{
				erroMessage.textContent = "Probleme de serveur!";
				erroMessage.hidden = false;
			}
			finally
			{
				submitButton.disabled = false; //reactiver a la fin de request
			}
	});
});





/*

Même chose mais avec du code moderne, retire car dans le sujet il est demandé d'utiliser le JS compatible avec Chrome >= 46 && Firefox >= 41


const likeButton = document.querySelectorAll('.like-button');
const commentButton = document.querySelectorAll('.button-comment');
const cancelCommentButton = document.querySelectorAll('.cancel-comment');
const commentForm = document.querySelectorAll('.form-comment');

const tokenCsrf = document.getElementById('csrf-token')?.value;

function createComment(comment)
{
	const container = document.createElement('div');
	container.classList.add('comment');

	const text = document.createElement('p');

	const username = document.createElement('strong');
	username.textContent = comment.username;

	const message = document.createTextNode(` : ${comment.message}`);

	text.append(username);
	text.append(message);

	const date = document.createElement('small');
	date.textContent = comment.createdAt;

	container.append(text);
	container.append(date);

	return container;

}
//Bouton pour afficher le champ de commentaire
commentButton.forEach((button) => {
	button.addEventListener('click', () => {
		const article = button.closest('.gallery-image');
		const form = article.querySelector('.form-comment');

		form.hidden = false;//form devient visible
		button.hidden = true;//Bouton dispares
	});
});

//Bouton pour annuler commantaire
cancelCommentButton.forEach((button) => {
	button.addEventListener('click', () => {
		const article = button.closest('.gallery-image');
		const form = article.querySelector('.form-comment');
		const commentButton = article.querySelector('.button-comment');
		const inputCans = form.querySelector('.comment-input');

		inputCans.value = "";//on supprime le contenu de input
		const errorMessage = form.querySelector('.msg-error-comment');
		errorMessage.textContent = '';
		errorMessage.hidden = true;
		form.hidden = true;//on cache le input de form
		commentButton.hidden = false;//Bouton pour ajouter commantaire devient visible
	});
});

likeButton.forEach((button) => {
	button.addEventListener('click', async () => {
			
			const article = button.closest('.gallery-image');
			const errorMessage = article.querySelector('.error-massage');
			const likeNumber = article.querySelector('.like-number');

			const formData = new FormData();
			const imageId = button.dataset.imageId;
			formData.append('image_id', imageId);
			formData.append('csrf_token', tokenCsrf);

			try {
				button.disabled = true;

				const res = await fetch("/image/like", {
					method: "POST",
					body: formData
				});

				if (!res.ok)
				{
					errorMessage.textContent = "Une erreur est survenue!";
					errorMessage.hidden = false;
					return;
				}

			
				const data = await res.json();
				

				if (data.success)
				{
					likeNumber.textContent = data.likeNumber;

					if (data.like)
						button.textContent = 'Retirer le like';
					else
						button.textContent = 'Like';

					errorMessage.textContent = '';
					errorMessage.hidden = true;
				}
				else
				{
					errorMessage.textContent = data.message;
					errorMessage.hidden = false;
				}

			} catch 
			{
				errorMessage.textContent = "Erreur est survenue!";
				errorMessage.hidden = false;
			}
			finally{
				button.disabled = false;
			}
	});
});

//Commentaires
//On insltale event listener pour chaque form. On lance si bouton submit a cliqué
commentForm.forEach((form) => {
	form.addEventListener('submit', async (event) => {
		event.preventDefault();//On 

		const imageId = form.dataset.imageId;
		const input = form.querySelector('.comment-input');
		const message = input.value.trim();

		const erroMessage = form.querySelector('.msg-error-comment');

		if (!message)
		{
			erroMessage.textContent = 'Le commentaire ne doit pas etre vide!';
			erroMessage.hidden = false;
			return;
		}

			const formData = new FormData();
			formData.append('image_id', imageId);
			formData.append('message', message);
			formData.append('csrf_token', tokenCsrf);

		const submitButton = form.querySelector('button[type="submit"]');

		submitButton.disabled = true;//on a besoin de desactive le bouton de submit de formulare pour n'est pas pouvoir envoier plusieurs

			try {
				const res = await fetch("/image/comment", {
					method: "POST",
					body: formData
				});

				if (!res.ok)
				{
					erroMessage.textContent = "Une erreur est survenue!";
					erroMessage.hidden = false;
					return;
				}

			
				const data = await res.json();
				

				if (!data.success)
				{
					erroMessage.textContent = data.message;
					erroMessage.hidden = false;
					return;
				}

				const parentComment = form.closest('.comments');
				const comment = createComment(data.comment);
				const showButton = form.closest('.comments').querySelector('.button-comment');

				parentComment.insertBefore(comment, showButton);

				input.value = "";
				erroMessage.textContent = '';
				erroMessage.hidden = true;

				form.hidden = true;

				
				showButton.hidden = false;

			} catch 
			{
				erroMessage.textContent = "Probleme de serveur!";
				erroMessage.hidden = false;
			}
			finally
			{
				submitButton.disabled = false; //reactiver a la fin de request
			}
	});
});
*/