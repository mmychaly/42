<?php

session_set_cookie_params([
	'httponly' => true,
	'samesite' => 'Lax'
]);

session_start();

$path = parse_url($_SERVER['REQUEST_URI'], PHP_URL_PATH);
$method = $_SERVER['REQUEST_METHOD'];

require_once __DIR__ . '/../src/common/auth.php';

if ($path === '/') {
    if (isUserSession()) {
        echo 'Bonjour ' . htmlspecialchars($_SESSION['username']);
		?>
        <form action="/logout" method="POST">
            <button type="submit">Se déconnecter</button>
        </form>
        <?php
    } else {
        echo 'Vous n\'êtes pas connecté.';
    }
	exit;
}

if ($path === '/login' && $method === 'GET')
{
	if (isUserSession()) {
		header('Location: /');
		exit;
	}

	require __DIR__  . '/../src/user/login_input.php';
	exit;
}

if ($path === '/login' && $method === 'POST')
{
	if (isUserSession()) {
		header('Location: /');
		exit;
	}

	require __DIR__  . '/../src/user/login_check.php';
	exit;
}

if ($path === '/register' && $method === 'GET')
{
	if (isUserSession()) {
		header('Location: /');
		exit;
	}
	require __DIR__  . '/../src/user/register_input.php';
	exit;
}

if ($path === '/register' && $method === 'POST')
{
	if (isUserSession()) {
		header('Location: /');
		exit;
	}

	require __DIR__  . '/../src/user/register_check.php';
	exit;
}

if ($path === '/logout' && $method === 'POST')
{
	require __DIR__  . '/../src/user/logout.php';
	exit;
}

if ($path === '/verify-email' && $method === 'GET')
{
	require __DIR__  . '/../src/user/email_verify.php';
	exit;
}

http_response_code(404);
echo '404 - Page not found';