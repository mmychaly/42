<?php

session_set_cookie_params([
	'httponly' => true,
	'samesite' => 'Lax'
]);
//JS can't read cookis
//Dont send cookis to other site

session_start();//Start session php or extract existing session

$path = parse_url($_SERVER['REQUEST_URI'], PHP_URL_PATH);//Extract URL of request 
$method = $_SERVER['REQUEST_METHOD'];//Extract method of request 

require_once __DIR__ . '/../src/common/auth.php';//Add code from auth
require_once __DIR__ . '/../src/common/csrf.php';//Add code from csrf

//Main page.Accessible for user connected and not. Display html page
if (($path === '/' || $path === '/image/gallery') && $method === 'GET') {
 
	require __DIR__  . '/../src/gallery/gallery_input.php';//Exit after execute this code 
	exit;
}

//Page html with form for register user in the server
if ($path === '/register' && $method === 'GET')
{
	if (isUserSession()) {
		header('Location: /');
		exit;
	}
	require __DIR__  . '/../src/user/register_input.php';
	exit;
}

//Request with data of user to register user in server.
if ($path === '/register' && $method === 'POST')
{
	if (isUserSession()) {
		header('Location: /');
		exit;
	}
	ckeckCsrf('/register');

	require __DIR__  . '/../src/user/register_check.php';
	exit;
}

if ($path === '/verify-email' && $method === 'GET')
{
	require __DIR__  . '/../src/user/email_verify.php';
	exit;
}

//Display login page.Html where user can login 
if ($path === '/login' && $method === 'GET')
{
	//Check user connected or not.If user is connected redirection to main page
	if (isUserSession()) {
		header('Location: /');
		exit;
	}

	require __DIR__  . '/../src/user/login_input.php';
	exit;
}

//Request with user data for connect user to server
if ($path === '/login' && $method === 'POST')
{
	if (isUserSession()) {
		header('Location: /');
		exit;
	}

	ckeckCsrf('/login');

	require __DIR__  . '/../src/user/login_check.php';
	exit;
}

if ($path === '/logout' && $method === 'POST')
{
	checkSession();
	ckeckCsrf();

	require __DIR__  . '/../src/user/logout.php';
	exit;
}



//Bloc for forgot password

//Layout of request of email
if ($path === '/password-forgot' && $method === 'GET')
{
	if (isUserSession()) {
		header('Location: /');
		exit;
	}

	require __DIR__  . '/../src/user/password_forgot_input.php';
	exit;
}

if ($path === '/password-forgot' && $method === 'POST')
{
	ckeckCsrf('/password-forgot');

	require __DIR__  . '/../src/user/password_forgot_check.php';
	exit;
}

//Routes pour modification de mot de passe
if ($path === '/password-reset' && $method === 'GET')
{
	if (isUserSession()) {
		header('Location: /');
		exit;
	}

	require __DIR__  . '/../src/user/password_reset_input.php';
	exit;
}

if ($path === '/password-reset' && $method === 'POST')
{
	$resetToken = $_POST['token'] ?? '';
	$redirReset = '/password-forgot';

	if (is_string($resetToken) && strlen($resetToken) === 64 && ctype_xdigit($resetToken))
		$redirReset = '/password-reset?token=' . rawurlencode($resetToken);
	ckeckCsrf($redirReset);
	
	require __DIR__  . '/../src/user/password_reset_check.php';
	exit;
}

//Display profil
if ($path === '/profile' && $method === 'GET')
{
	checkSession();
	require __DIR__  . '/../src/user/profile_input.php';
	exit;
}

if ($path === '/profile' && $method === 'POST')
{
	checkSession();
	ckeckCsrf('/profile');
	require __DIR__  . '/../src/user/profile_check.php';
	exit;
}

if ($path === '/profile/password' && $method === 'POST')
{
	checkSession();
	ckeckCsrf('/profile');

	require __DIR__  . '/../src/user/profile_password_check.php';
	exit;
}

//editor
if ($path === '/editor' && $method === 'GET')
{
	checkSession();
	require __DIR__  . '/../src/image/editor_input.php';
	exit;
}

if ($path === '/image/create' && $method === 'POST')
{
	checkSession(true);
	ckeckCsrf('/', true);

	require __DIR__  . '/../src/image/create_image.php';
	exit;
}

if ($path === '/image/delete' && $method === 'POST')
{
	checkSession(true);
	ckeckCsrf('/', true);

	require __DIR__  . '/../src/image/delete_image.php';
	exit;
}


if ($path === '/image/like' && $method === 'POST')
{
	checkSession(true);
	ckeckCsrf('/', true);

	require __DIR__  . '/../src/gallery/like_image.php';
	exit;
}

if ($path === '/image/comment' && $method === 'POST')
{
	checkSession(true);
	ckeckCsrf('/', true);

	require __DIR__  . '/../src/gallery/comment_image.php';
	exit;
}

//http_response_code(404); //Le subject n'est pas trop clair pour 404
?>

<!DOCTYPE html>
<html lang="fr">
<head>
	<meta charset="UTF-8">
	<meta name="viewport" content="width=device-width, initial-scale=1.0">
	<link rel="stylesheet" href="/css/site.css">
	<title>Page introuvable</title>
</head>
<body>
	<?php require __DIR__  . '/../src/common/header.php'; ?>
		<main class="site-main">
			<h1>404-Page introuvable</h1>
			<p>La page demandée n'existe pas</p>
			<p><a href="/">Retour à l'accueil</a></p>
		</main>
	<?php require __DIR__  . '/../src/common/footer.php'; ?>
</body>
</html>