const likeButton = document.querySelectorAll('.like-button');


likeButton.forEach((button) => {
	button.addEventListener('click', async () => {
			
			const formData = new FormData();
			const imageId = button.dataset.imageId;
			formData.append('image_id', imageId);

			try {
				const res = await fetch("/image/like", {
					method: "POST",
					body: formData
				});

				if (!res.ok)
					return;
			
				const data = await res.json();

				if (data.success)
				{
					const article = button.closest('.gallery-image');
					const likeNumber = article.querySelector('.like-number');

					likeNumber.textContent = data.likeNumber;

					if (data.like)
						button.textContent = 'Retirer le like';
					else
						button.textContent = 'Like';
				}

			} catch 
			{
				console.log('Erreur serveur!');
			}
	});
});