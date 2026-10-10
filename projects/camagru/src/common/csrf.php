<?php

// CSRF protection: checks whether the request comes from our form/session.

// Create a CSRF token.
function tokenCsrf(): string
{
	if (empty($_SESSION['csrf_token'])) // Create the token if it does not exist.
		$_SESSION['csrf_token'] = bin2hex(random_bytes(32));

	return $_SESSION['csrf_token'];
}

// Verify the CSRF token.
function ckeckCsrf(string $redirTo = '/', bool $isAjax = false): void
{
	// Extract the CSRF token sent with the request.
	$token = $_POST['csrf_token'] ?? '';

	// If the received token matches the token stored in the session,
	// allow the request.
	if (
		is_string($token) &&
		isset($_SESSION['csrf_token']) &&
		is_string($_SESSION['csrf_token']) &&
		hash_equals($_SESSION['csrf_token'], $token)
	)
	{
		return;
	}

	// For a fetch/AJAX request, stop and return a JSON error.
	if ($isAjax)
	{
		header('Content-Type: application/json; charset=utf-8');

		echo json_encode([
			'success' => false,
			'message' => 'Requete invalide ou session expirée!'
		]);
		exit;
	}

	// For a normal request, store the error and redirect
	// to the original page.
	$_SESSION['csrf_error'] = 'Requete invalide ou session expirée!';
	header('Location: ' . $redirTo , true, 303);
	exit;
}