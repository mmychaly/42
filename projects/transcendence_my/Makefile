name =  transcendence
all:
		@docker-compose up -d

build:
		@docker-compose up -d --build

debug:
# Get nginx messages
		@docker-compose up --build

down:
# Stopping configuration
		@docker-compose  down

re: down
# Rebuilding the configuration
		@docker-compose up -d --build

clean: down
# Clearing the configuration
		@docker system prune -a --force

fclean:
# Clearing total of the all configurations
		@docker-compose down -v
		@docker system prune -a --force

.PHONY  : all build debug down re clean fclean