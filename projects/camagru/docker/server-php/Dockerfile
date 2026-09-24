FROM docker.io/library/php:8.4-fpm
RUN apt-get update && apt-get install -y \
	libjpeg62-turbo-dev \
	libpng-dev \
	&& docker-php-ext-configure gd --with-jpeg \
	&& docker-php-ext-install pdo pdo_mysql gd \
	&& rm -rf /var/lib/apt/lists/*

COPY ./docker/server-php/camagru.ini /usr/local/etc/php/conf.d/99-camagru.ini	

WORKDIR /var/www/html
