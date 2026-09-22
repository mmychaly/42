const likeButton = document.querySelectorAll('.like-button');
const commentButton = document.querySelectorAll('.button-comment');
const cancelCommentButton = document.querySelectorAll('.cancel-comment');
const commentForm = document.querySelectorAll('.form-comment')

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

commentButton.forEach((button) => {
	button.addEventListener('click', () => {
		const article = button.closest('.gallery-image');
		const form = article.querySelector('.form-comment');

		form.hidden = false;
		button.hidden = true;
	});
});

cancelCommentButton.forEach((button) => {
	button.addEventListener('click', () => {
		const article = button.closest('.gallery-image');
		const form = article.querySelector('.form-comment');
		const commentButton = article.querySelector('.button-comment');
		
		form.hidden = true;
		commentButton.hidden = false;
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

commentForm.forEach((form) => {
	form.addEventListener('submit', async (event) => {
		event.preventDefault();

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
				erroMessage.hidden = true;

				form.hidden = true;

				
				showButton.hidden = false;

			} catch 
			{
				erroMessage.textContent = "Probleme de serveur!";
				erroMessage.hidden = false;
			}
	});
});