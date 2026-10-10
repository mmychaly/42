// Like buttons.
var likeButton = document.querySelectorAll('.like-button');

// Buttons used to display the comment form.
var commentButton = document.querySelectorAll('.button-comment');

// Buttons used to cancel a comment.
var cancelCommentButton = document.querySelectorAll('.cancel-comment');

// Comment forms.
var commentForm = document.querySelectorAll('.form-comment');

var elementCsrf = document.getElementById('csrf-token');
var tokenCsrf = elementCsrf ? elementCsrf.value : '';


// Create the HTML elements used to display a new comment without reloading the page.
function createComment(comment)
{
	var container = document.createElement('div');// Main container.
	container.classList.add('comment');// Add the comment class.

	var text = document.createElement('p');// Element containing the username and message.

	var username = document.createElement('strong');
	username.textContent = comment.username;

	var message = document.createTextNode(' : ' + comment.message);

	text.appendChild(username);
	text.appendChild(message);

	var date = document.createElement('small');// Element containing the creation date.
	date.textContent = comment.createdAt;

	// Add the elements to the comment container.
	container.appendChild(text);
	container.appendChild(date);

	return container;
}

// Add a click event to the button that displays the comment form.
function eventCommentButton(button)
{
	button.addEventListener('click', function () {

		var article = button.closest('.gallery-image');// Find the image article containing the clicked button.
		var form = article.querySelector('.form-comment');// Find the comment form belonging to this image.

		form.hidden = false;// Show the comment form.
		button.hidden = true;// Hide the button.
	});
}

// Attach the comment-button event handler to each comment button.
for (var i = 0; i < commentButton.length; i++)
{
	eventCommentButton(commentButton[i]);
}

// Add a click event to the button that cancels the comment.
function eventCancelCommentButton(button)
{
	button.addEventListener('click', function () {
		var article = button.closest('.gallery-image');
		var form = article.querySelector('.form-comment');
		var showCommentButton = article.querySelector('.button-comment');
		var inputComment = form.querySelector('.comment-input');
		var errorMessage = form.querySelector('.msg-error-comment');

		inputComment.value = '';// Clear the comment input.

		errorMessage.textContent = '';// Clear any previous error message.
		errorMessage.hidden = true; // Hide the error message.

		form.hidden = true;// Hide the comment form.

		showCommentButton.hidden = false;// Show the button used to add a comment.
	});
}

// Attach the cancel-comment event handler to each cancel button.
for (var i = 0; i < cancelCommentButton.length; i++)
{
	eventCancelCommentButton(cancelCommentButton[i]);
}


// Add a click event to each like button to add or remove a like.
function eventlikeButton(button)
{
	button.addEventListener('click', function () {
		var article = button.closest('.gallery-image');
		var errorMessage = article.querySelector('.error-massage');
		var likeNumber = article.querySelector('.like-number');

		var formData = new FormData();
		var imageId = button.dataset.imageId;

		formData.append('image_id', imageId);// Add the image ID to the request.
		formData.append('csrf_token', tokenCsrf);// Add the user CSRF token.

		button.disabled = true;// Temporarily disable the like button.

		// Send a request to the server to add or remove a like.
		fetch("/image/like", {
			method: "POST",
			credentials: 'same-origin',
			body: formData
		})
		.then(function (res) {
			if (!res.ok)// Check the HTTP response and display an error if needed.
			{
				errorMessage.textContent = "Une erreur est survenue!";
				errorMessage.hidden = false;
				return null;
			}

			return res.json();// Parse the JSON response from the server.
		})
		.then(function (data) {
			if (data === null)// Stop if there is no usable response.
				return;

			if (data.success)// If the request succeeded, update the displayed data.
			{
				likeNumber.textContent = data.likeNumber;// Update the displayed number of likes.

				if (data.like)// If the user liked the image, allow the like to be removed.
					button.textContent = 'Retirer le like';
				else// If the like was removed, allow the image to be liked again.
					button.textContent = 'Like';

				errorMessage.textContent = '';
				errorMessage.hidden = true;
			}
			else// If the server reports an error, display its message.
			{
				errorMessage.textContent = data.message;
				errorMessage.hidden = false;
			}
		})
		.catch(function () {
			errorMessage.textContent = "Erreur est survenue!";
			errorMessage.hidden = false;
		})
		.then(function () {
			button.disabled = false;// Re-enable the like button when the request is finished.
		});
	});
}

// Attach the like event handler to each like button.
for (var i = 0; i < likeButton.length; i++)
{
	eventlikeButton(likeButton[i]);
}

// Comments.
// Attach a submit event listener to each comment form and send the request with fetch.
function eventCommentForm(form)
{
	form.addEventListener('submit', function (event) {
		event.preventDefault();// Prevent the default form submission and page reload.

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
		submitButton.disabled = true;// Disable the submit button to prevent multiple simultaneous submissions.

		// Send the comment to the server with fetch.
		fetch("/image/comment", {
			method: "POST",
			credentials: 'same-origin',
			body: formData
		})
		.then(function (res) {
			if (!res.ok)// Check the HTTP response and display an error if needed.
			{
				erroMessage.textContent = "Une erreur est survenue!";
				erroMessage.hidden = false;
				return null;
			}

			return res.json();// Parse the JSON response from the server.
		})
		.then(function (data) {
			if (data === null)// Stop if there is no usable response.
				return;

			if (!data.success)// Stop if the server reports an error.
			{
				erroMessage.textContent = data.message;
				erroMessage.hidden = false;
				return;
			}

			var parentComment = form.closest('.comments');// Find the parent comments container.
			var comment = createComment(data.comment);// Create the new comment element.
			var showButton = parentComment.querySelector('.button-comment');// Find the element before which the new comment should be inserted.

			parentComment.insertBefore(comment, showButton);// Insert the new comment into the page before the button.

			input.value = "";// Clear the comment input.
				
			erroMessage.textContent = '';// Clear the error message.
			erroMessage.hidden = true;// Hide the error message.

			form.hidden = true;// Hide the comment form.
			showButton.hidden = false;// Show the button used to add another comment.
		})
		.catch(function () {
			erroMessage.textContent = "Erreur est survenue!";
			erroMessage.hidden = false;
		})
		.then(function () {
			submitButton.disabled = false;// Re-enable the comment submit button when the request is finished.
		});

	});
}

// Attach the comment form handler to each form.
for (var i = 0; i < commentForm.length; i++)
{
	eventCommentForm(commentForm[i]);
}