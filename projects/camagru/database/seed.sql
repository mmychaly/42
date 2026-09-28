INSERT IGNORE INTO users (
	username, 
	email, 
	password,
	email_check,
	email_check_once
)
VALUES (
	'test',
	'mickael.mychalyszyn@gmail.com',
	'$2y$12$VDl3LowNm/cBRMqG2HvAYuJ8obSKrWoywvNPUZnMWNQcldCm2VbO.',
	1,
	1
);