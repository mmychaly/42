<?php

function readFullResponse($socket): string
{
	$response = '';
	
	while (($line = fgets($socket, 515)) !== false)
	{
		$response .= $line;
		if(strlen($line) >= 4 && $line[3] === ' ')
			break;
	}

	return $response;
}

function sendVerifEmail(string $username, string $email, string $verifLink): bool
{

	//on recuper les variable d'envirenement de SMTP dans les variable
	$smtpUser = getenv('SMTP_USER');
	$smtpPassword = getenv('SMTP_PASSWORD');
	$smtpHost = getenv('SMTP_HOST');
	$smtpPort = getenv('SMTP_PORT');
	$smtpFrom = getenv('SMTP_FROM');

	////Create connection with SMTP serveur
	$socket = stream_socket_client("tcp://$smtpHost:$smtpPort", $errorNumber, $errorMessage, 30);
	if ($socket === false)
		return false;

	$responseSMTP = readFullResponse($socket);
	if (substr($responseSMTP, 0, 3) !== '220') //For first message he must send 220
	{
		fclose($socket);
		return false;
	}

	fwrite($socket, "EHLO localhost\r\n"); //Say at server Smpt name of client
	$responseSMTP = readFullResponse($socket);
	if (substr($responseSMTP, 0, 3) !== '250') //For seconde and next 250 , if smtp dont return 250 we have the problem.
	{
		fclose($socket);
		return false;
	}

	fwrite($socket, "STARTTLS\r\n"); //Launch TLS protocol for transmition name and password
	$responseSMTP = readFullResponse($socket);
	if (substr($responseSMTP, 0, 3) !== '220')
	{
		fclose($socket);
		return false;
	}

	//We need trasform socket of TCP protocol towards TLS protocol 
	$tlsEnabled = stream_socket_enable_crypto($socket, true, STREAM_CRYPTO_METHOD_TLS_CLIENT);
	if ($tlsEnabled !== true)
	{
		fclose($socket);
		return false;
	}

	fwrite($socket, "EHLO localhost\r\n");//After TLS , we need send second time
	$responseSMTP = readFullResponse($socket);
	if (substr($responseSMTP, 0, 3) !== '250')
	{
		fclose($socket);
		return false;
	}

	//AUTH LOGIN, send email and pasword
	fwrite($socket, "AUTH LOGIN\r\n"); //We want use autification in SMTP server
	$responseSMTP = readFullResponse($socket);
	if (substr($responseSMTP, 0, 3) !== '334') //334 Server SMTP wait next part
	{
		fclose($socket);
		return false;
	}

	fwrite($socket, base64_encode($smtpUser) . "\r\n"); //Send email en base64
	$responseSMTP = readFullResponse($socket);
	if (substr($responseSMTP, 0, 3) !== '334')
	{
		fclose($socket);
		return false;
	}

	fwrite($socket, base64_encode($smtpPassword) . "\r\n"); //Send password at server SMTP en base64
	$responseSMTP = readFullResponse($socket);
	if (substr($responseSMTP, 0, 3) !== '235') //235 mean Auth succes
	{
		fclose($socket);
		return false;
	}

	fwrite($socket, "MAIL FROM:<$smtpFrom>\r\n"); //We say who send email.
	$responseSMTP = readFullResponse($socket);
	if (substr($responseSMTP, 0, 3) !== '250') 
	{
		fclose($socket);
		return false;
	}

	fwrite($socket, "RCPT TO:<$email>\r\n"); //We define who recive the email.
	$responseSMTP = readFullResponse($socket);
	if (substr($responseSMTP, 0, 3) !== '250' && substr($responseSMTP, 0, 3) !== '251') 
	{
		fclose($socket);
		return false;
	}

	fwrite($socket, "DATA\r\n"); //Send the mail
	$responseSMTP = readFullResponse($socket);
	if (substr($responseSMTP, 0, 3) !== '354') //Start input
	{
		fclose($socket);
		return false;
	}

	$subject = 'Verification Camagru';
	$body = "Bonjour $username, \r\n"
			. "Vous devez confirmer votre email, pour finaliser votre inscription sur Camagru.\r\n"
			. "Cliquez sur le lien: $verifLink\r\n"
			. "Cordialement.\r\n\r\n"
			. "L'equipe Camagru.\r\n";

	$headers =
		"From: Camagru <$smtpFrom>\r\n"
		. "To: <$email>\r\n"
		. "Subject: $subject\r\n"
		. "MIME-Version: 1.0\r\n"
		. "Content-Type: text/plain; charset=UTF-8\r\n";
	
	$message = $headers . "\r\n" . $body;

	fwrite($socket, $message . "\r\n.\r\n"); // Send message
	$responseSMTP = readFullResponse($socket);
	if (substr($responseSMTP, 0, 3) !== '250') 
	{
		fclose($socket);
		return false;
	}

	fwrite($socket, "QUIT\r\n");
	readFullResponse($socket);
	fclose($socket);
	return true;
}