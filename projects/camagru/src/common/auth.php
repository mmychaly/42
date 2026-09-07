<?php

function isUserSession(): bool
{
	return isset($_SESSION['user_id']);
}

function checkSession(): void
{
	if (!isUserSession()) {
		header('Location: /login');
		exit;
	}
}