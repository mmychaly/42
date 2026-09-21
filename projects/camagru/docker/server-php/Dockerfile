FROM docker.io/library/php:8.4-fpm
RUN apt-get update && apt-get install -y \
	libjpeg62-turbo-dev \
	libpng-dev \
	&& docker-php-ext-configure gd --with-jpeg \
	&& docker-php-ext-install pdo pdo_mysql gd \
	&& rm -rf /var/lib/apt/lists/*
	
WORKDIR /var/www/html


RUN mkdir -p /var/www/html/uploads \
	&& chown -R www-data:www-data /var/www/html/uploads