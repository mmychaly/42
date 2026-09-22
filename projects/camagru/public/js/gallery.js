const likeButton = document.querySelectorAll('.like-button');
const commentButton = document.querySelectorAll('.button-comment');
const cancelCommentButton = document.querySelector('.cancel-comment');


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