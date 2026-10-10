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

	// Get the SMTP configuration from environment variables.
	$smtpUser = getenv('SMTP_USER');
	$smtpPassword = getenv('SMTP_PASSWORD');
	$smtpHost = getenv('SMTP_HOST');
	$smtpPort = getenv('SMTP_PORT');
	$smtpFrom = getenv('SMTP_FROM');

	// Create a TCP connection to the SMTP server.
	$socket = @stream_socket_client("tcp://$smtpHost:$smtpPort", $errorNumber, $errorMessage, 30);
	if ($socket === false)
		return false;

	$responseSMTP = readFullResponse($socket);
	if (substr($responseSMTP, 0, 3) !== '220') // The SMTP server must respond with code 220 when the connection is established.
	{
		fclose($socket);
		return false;
	}

	// Send the client identification to the SMTP server.
	if (!smtpWrite($socket, "EHLO localhost\r\n"))
	{
		fclose($socket);
		return false;
	}

	$responseSMTP = readFullResponse($socket);
	if (substr($responseSMTP, 0, 3) !== '250') // The SMTP server must respond with code 250 after EHLO.
	{
		fclose($socket);
		return false;
	}

	// Request a secure TLS connection before sending credentials.
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

	// Upgrade the TCP socket to a TLS-encrypted connection.
	$tlsEnabled = @stream_socket_enable_crypto($socket, true, STREAM_CRYPTO_METHOD_TLS_CLIENT);
	if ($tlsEnabled !== true)
	{
		fclose($socket);
		return false;
	}

	// Send EHLO again after enabling TLS.
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

	// Start SMTP authentication with AUTH LOGIN.
	if (!smtpWrite($socket, "AUTH LOGIN\r\n"))// Request authentication on the SMTP server.
	{
		fclose($socket);
		return false;
	}
	
	$responseSMTP = readFullResponse($socket);
	if (substr($responseSMTP, 0, 3) !== '334') // Code 334 means the SMTP server is waiting for the next authentication value.
	{
		fclose($socket);
		return false;
	}

	// Send the SMTP username encoded in Base64.
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

	// Send the SMTP password encoded in Base64.
	if (!smtpWrite($socket, base64_encode($smtpPassword) . "\r\n"))
	{
		fclose($socket);
		return false;
	}
	 
	$responseSMTP = readFullResponse($socket);
	if (substr($responseSMTP, 0, 3) !== '235') // Code 235 means authentication was successful.
	{
		fclose($socket);
		return false;
	}

	// Define the sender email address.
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

	// Define the recipient email address.
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

	// Tell the SMTP server that the email content will follow.
	if (!smtpWrite($socket, "DATA\r\n"))
	{
		fclose($socket);
		return false;
	}
	
	$responseSMTP = readFullResponse($socket);
	if (substr($responseSMTP, 0, 3) !== '354') // Code 354 means the server is ready to receive the message content.
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

	// Send the email headers and body.
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