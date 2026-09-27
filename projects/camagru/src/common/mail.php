<?php

function readFullResponse($socket): string
{
	$response = '';
	
	while (true)
	{
		$line = @fgets($socket, 515);
		if ($line === false)
			return '';
		$response .= $line;
		if(strlen($line) >= 4 && $line[3] === ' ')
			return $response;
	}
}

function smtpWrite($socket, string $message): bool
{
	$len = strlen($message);
	$offset = 0;

	while ($offset < $len)
	{
		$res = @fwrite($socket, substr($message, $offset));

		if ($res === false  || $res === 0)
			return false;

		$offset += $res;
	}

	return true;
}

function sendEmail(string $email, string $subject, string $body): bool
{

	//on recuper les variable d'envirenement de SMTP dans les variable
	$smtpUser = getenv('SMTP_USER');
	$smtpPassword = getenv('SMTP_PASSWORD');
	$smtpHost = getenv('SMTP_HOST');
	$smtpPort = getenv('SMTP_PORT');
	$smtpFrom = getenv('SMTP_FROM');

	////Create connection with SMTP serveur
	$socket = @stream_socket_client("tcp://$smtpHost:$smtpPort", $errorNumber, $errorMessage, 30);
	if ($socket === false)
		return false;

	$responseSMTP = readFullResponse($socket);
	if (substr($responseSMTP, 0, 3) !== '220') //For first message he must send 220
	{
		fclose($socket);
		return false;
	}

	//Say at server Smpt name of client
	if (!smtpWrite($socket, "EHLO localhost\r\n"))
	{
		fclose($socket);
		return false;
	}

	$responseSMTP = readFullResponse($socket);
	if (substr($responseSMTP, 0, 3) !== '250') //For seconde and next 250 , if smtp dont return 250 we have the problem.
	{
		fclose($socket);
		return false;
	}

	//Launch TLS protocol for transmition name and password
	if (!smtpWrite($socket, "STARTTLS\r\n"))
	{
		fclose($socket);
		return false;
	}

	$responseSMTP = readFullResponse($socket);
	if (substr($responseSMTP, 0, 3) !== '220')
	{
		fclose($socket);
		return false;
	}

	//We need trasform socket of TCP protocol towards TLS protocol 
	$tlsEnabled = @stream_socket_enable_crypto($socket, true, STREAM_CRYPTO_METHOD_TLS_CLIENT);
	if ($tlsEnabled !== true)
	{
		fclose($socket);
		return false;
	}

	//After TLS , we need send second time
	if (!smtpWrite($socket, "EHLO localhost\r\n"))
	{
		fclose($socket);
		return false;
	}
	$responseSMTP = readFullResponse($socket);
	if (substr($responseSMTP, 0, 3) !== '250')
	{
		fclose($socket);
		return false;
	}

	//AUTH LOGIN, send email and pasword
	if (!smtpWrite($socket, "AUTH LOGIN\r\n"))//We want use autification in SMTP server
	{
		fclose($socket);
		return false;
	}
	
	$responseSMTP = readFullResponse($socket);
	if (substr($responseSMTP, 0, 3) !== '334') //334 Server SMTP wait next part
	{
		fclose($socket);
		return false;
	}

	//Send email en base64
	if (!smtpWrite($socket, base64_encode($smtpUser) . "\r\n"))
	{
		fclose($socket);
		return false;
	}

	$responseSMTP = readFullResponse($socket);
	if (substr($responseSMTP, 0, 3) !== '334')
	{
		fclose($socket);
		return false;
	}

	//Send password at server SMTP en base64
	if (!smtpWrite($socket, base64_encode($smtpPassword) . "\r\n"))
	{
		fclose($socket);
		return false;
	}
	 
	$responseSMTP = readFullResponse($socket);
	if (substr($responseSMTP, 0, 3) !== '235') //235 mean Auth succes
	{
		fclose($socket);
		return false;
	}

	//We say who send email
	if (!smtpWrite($socket, "MAIL FROM:<$smtpFrom>\r\n"))
	{
		fclose($socket);
		return false;
	}

	$responseSMTP = readFullResponse($socket);
	if (substr($responseSMTP, 0, 3) !== '250') 
	{
		fclose($socket);
		return false;
	}

	//We define who recive the email.
	if (!smtpWrite($socket, "RCPT TO:<$email>\r\n"))
	{
		fclose($socket);
		return false;
	}
	 
	$responseSMTP = readFullResponse($socket);
	if (substr($responseSMTP, 0, 3) !== '250' && substr($responseSMTP, 0, 3) !== '251') 
	{
		fclose($socket);
		return false;
	}

	//Send the mail
	if (!smtpWrite($socket, "DATA\r\n"))
	{
		fclose($socket);
		return false;
	}
	
	$responseSMTP = readFullResponse($socket);
	if (substr($responseSMTP, 0, 3) !== '354') //Start input
	{
		fclose($socket);
		return false;
	}

	$headers =
		"From: Camagru <$smtpFrom>\r\n"
		. "To: <$email>\r\n"
		. "Subject: $subject\r\n"
		. "MIME-Version: 1.0\r\n"
		. "Content-Type: text/plain; charset=UTF-8\r\n";
	
	$message = $headers . "\r\n" . $body;

	// Send message
	if (!smtpWrite($socket, $message . "\r\n.\r\n"))
	{
		fclose($socket);
		return false;
	}

	$responseSMTP = readFullResponse($socket);
	if (substr($responseSMTP, 0, 3) !== '250') 
	{
		fclose($socket);
		return false;
	}

	smtpWrite($socket, "QUIT\r\n");	
	fclose($socket);
	return true;
}

function sendVerifEmail(string $username, string $email, string $verifLink): bool
{
	$subject = 'Verification Camagru';
	
	$body = "Bonjour $username, \r\n"
			. "Vous devez confirmer votre email.\r\n"
			. "Cliquez sur le lien: $verifLink\r\n\r\n"
			. "Cordialement.\r\n\r\n"
			. "L'equipe Camagru.\r\n";

	return sendEmail($email, $subject, $body);
}

function sendResetPasswordEmail(string $username, string $email, string $resetLink): bool
{
	$subject = 'Reinitialisation du mot de passe Camagru';
	
	$body = "Bonjour $username, \r\n"
			. "Vous avez demandé la reinitialisation de votre mot de passe.\r\n"
			. "Cliquez sur le lien: $resetLink\r\n\r\n"
			. "Cordialement.\r\n\r\n"
			. "L'equipe Camagru.\r\n";

	return sendEmail($email, $subject, $body);
}

function sendCommentEmail(string $username, string $email): bool
{
	$subject = 'Nouveau commentaire Camagru';
	
	$body = "Bonjour $username, \r\n"
			. "Une personne a commenté l'une de vos images.\r\n\r\n"
			. "Cordialement.\r\n\r\n"
			. "Team Camagru.\r\n";

	return sendEmail($email, $subject, $body);
}