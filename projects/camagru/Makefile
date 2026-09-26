all: up

up:
	docker compose up -d --build
	docker compose exec -u 0 server-php chown -R www-data:www-data /var/www/html/uploads

down:
	docker compose down

ps:
	docker compose ps

clean:
	docker compose down --remove-orphans

fclean:
	docker compose down -v --remove-orphans

re: down up

.PHONY: all up down ps clean fclean re