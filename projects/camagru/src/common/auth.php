<?php

// Check whether the user is connected.
// Returns true if the session contains a user_id.
function isUserSession(): bool
{
	return isset($_SESSION['user_id']);
}

function checkSession(bool $isAjax = false): void
{
	// If the user is connected, allow the request.
	if (isUserSession()) {
		return;
	}

	// For a fetch/AJAX request, return a JSON error
	// if the user is not connected.
	if ($isAjax)
	{
		header('Content-Type: application/json; charset=utf-8');

		echo json_encode([
			'success' => false,
			'message' => 'Session expirée!'
		]);
		exit;
	}

	// For a normal request, redirect the user to the login page.
	// if the user is not connected.
	header('Location: /login', true, 303);
	exit;
}