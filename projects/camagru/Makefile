all: up

up:
	@docker compose up -d --build
	@docker compose exec -T -u 0 server-php chown -R www-data:www-data /var/www/html/uploads
	@docker compose exec -T db sh -c 'until MYSQL_PWD="$$MARIADB_PASSWORD" mariadb --protocol=tcp --disable-ssl-verify-server-cert -h 127.0.0.1 -u "$$MARIADB_USER" "$$MARIADB_DATABASE" -e "SELECT 1 FROM users LIMIT 0" >/dev/null 2>&1; do sleep 1; done; MYSQL_PWD="$$MARIADB_PASSWORD" mariadb --protocol=tcp --disable-ssl-verify-server-cert -h 127.0.0.1 -u "$$MARIADB_USER" "$$MARIADB_DATABASE" < /docker-entrypoint-initdb.d/02-seed.sql'



down:
	@docker compose down

ps:
	@docker compose ps

clean:
	@docker compose down --remove-orphans

fclean:
	@docker compose down -v --remove-orphans
	@docker system prune -a --force

re: down up

.PHONY: all up down ps clean fclean re