<?php

//Creation d'un token CSRF
function tokenCsrf(): string
{
	if (empty($_SESSION['csrf_token'])) //si token n'existe pas on va creer 
		$_SESSION['csrf_token'] = bin2hex(random_bytes(32));

	return $_SESSION['csrf_token'];
}

//Verification de tolen CSRF
function ckeckCsrf(): void
{
	$token = $_POST['csrf_token'] ?? '';

	if ( !is_string($token) || !isset($_SESSION['csrf_token']) || !hash_equals($_SESSION['csrf_token'], $token))
	{
		http_response_code(403);
		exit('Requête invalide');
	}
}