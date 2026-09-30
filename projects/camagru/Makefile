all: up

up:
	@output=$$(docker compose up -d --build 2>&1) || { printf '%s\n' "$$output"; exit 1; }
	@output=$$(docker compose exec -T -u 0 server-php chown -R www-data:www-data /var/www/html/uploads 2>&1) || { printf '%s\n' "$$output"; exit 1; }
	@output=$$(docker compose exec -T db sh -c 'until MYSQL_PWD="$$MARIADB_PASSWORD" mariadb --protocol=tcp --disable-ssl-verify-server-cert -h 127.0.0.1 -u "$$MARIADB_USER" "$$MARIADB_DATABASE" -e "SELECT 1 FROM users LIMIT 0" >/dev/null 2>&1; do sleep 1; done; MYSQL_PWD="$$MARIADB_PASSWORD" mariadb --protocol=tcp --disable-ssl-verify-server-cert -h 127.0.0.1 -u "$$MARIADB_USER" "$$MARIADB_DATABASE" < /docker-entrypoint-initdb.d/02-seed.sql' 2>&1) || { printf '%s\n' "$$output"; exit 1; }



down:
	@output=$$(docker compose down 2>&1) || { printf '%s\n' "$$output"; exit 1; }

ps:
	@docker compose ps

clean:
	@output=$$(docker compose down --remove-orphans 2>&1) || { printf '%s\n' "$$output"; exit 1; }

fclean:
	@output=$$(docker compose down -v --remove-orphans 2>&1) || { printf '%s\n' "$$output"; exit 1; }

re: down up

.PHONY: all up down ps clean fclean re