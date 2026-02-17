name =  transcendence

export DOCKER_API_VERSION = 1.44

all: front
		@docker-compose up -d

front:
	@cd frontend && npm install && npm run build

build: front
		@docker-compose up -d --build

debug:
# Get nginx messages
		@docker-compose up --build

down:
# Stopping configuration
		@docker-compose  down

re: down build
# Rebuilding the configuration


clean: down
# Clearing the configuration
		@docker system prune -a --force

fclean:
# Clearing total of the all configurations
		@docker-compose down -v
		@docker system prune -a --force

.PHONY  : all build debug down re clean fclean
