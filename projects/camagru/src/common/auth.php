<?php

function isUserSession(): bool
{
	return isset($_SESSION['user_id']);
}

function checkSession(bool $isAjax = false): void
{
	if (isUserSession()) {
		return;
	}

	if ($isAjax)
	{
		header('Content-Type: application/json; charset=utf-8');

		echo json_encode([
			'success' => false,
			'message' => 'Session expirée!'
		]);
		exit;
	}



	header('Location: /login', true, 303);
	exit;
}