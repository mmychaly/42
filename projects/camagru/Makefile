all: up

up:
	docker compose up -d --build

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