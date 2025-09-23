name =  inception
all:
		@printf " Running the configuration ${name}...\n"
		@bash srcs/requirements/wordpress/tools/dir.sh
		@docker-compose -f ./srcs/docker-compose.yml --env-file srcs/.env up -d

build:
		@printf " Configuration assembly ${name}...\n"
		@bash srcs/requirements/wordpress/tools/dir.sh
		@docker-compose -f ./srcs/docker-compose.yml --env-file srcs/.env up -d --build

down:
		@printf " Stopping configuration ${name}...\n"
		@docker-compose -f ./srcs/docker-compose.yml --env-file srcs/.env down

re: down
		@printf " Rebuilding the configuration ${name}...\n"
		@docker-compose -f ./srcs/docker-compose.yml --env-file srcs/.env up -d --build

clean: down
		@printf " Clearing the configuration ${name}...\n"
		@docker system prune -a
		@sudo rm -rf ~/data/wordpress/*
		@sudo rm -rf ~/data/mariadb/*

fclean:
		@printf " Clearing total of the all configurations ${name}...\n"
		@docker stop $$(docker ps -qa)
		@docker system prune -a --force --volumes
		@docker network prune --force
		@docker volume prune --force
		@sudo rm -rf ~/data/wordpress/*
		@sudo rm -rf ~/data/mariadb/*

.PHONY  : all build down re clean fclean