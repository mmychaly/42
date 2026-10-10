# Camagru

Camagru is a web application inspired by photo-sharing platforms.  
Users can create an account, confirm their email address, log in, create images using a webcam or an uploaded image, apply stickers, publish images, like posts and leave comments.

The project uses a native HTML/CSS/JavaScript frontend and a PHP backend running behind Nginx, with MariaDB as the database.

## Features

- User registration
- Email confirmation
- Login and logout
- Password reset by email
- Profile management
  - Change username
  - Change email
  - Change password
  - Enable or disable comment email notifications
- Public image gallery
- Pagination
- Likes
- Comments
- Email notification when an image receives a comment
- Image creation from:
  - Webcam
  - Uploaded JPEG/PNG image
- Multiple stickers / overlays
- Image deletion by its owner
- Responsive interface

## Security

The application includes several security mechanisms:

- Passwords are stored with `password_hash()` and verified with `password_verify()`
- PDO prepared statements are used for database queries
- CSRF tokens protect POST requests
- Session cookies use `HttpOnly` and `SameSite=Lax`
- User-generated content is escaped with `htmlspecialchars()` or inserted with safe DOM methods
- Reset and email-verification tokens are randomly generated and stored hashed in the database
- Image deletion checks that the image belongs to the authenticated user
- Uploaded files are validated on the server

## Technologies

- PHP / PHP-FPM
- MariaDB
- Nginx
- HTML
- CSS
- JavaScript
- Docker / Docker Compose
- PDO
- PHP GD
- SMTP

## Project structure


.
├── database/
│   └── schema.sql
├── docker/
│   ├── nginx/
│   └── server-php/
├── public/
│   ├── index.php
│   ├── css/
│   ├── js/
│   └── asset/
├── src/
│   ├── common/
│   ├── data/
│   ├── gallery/
│   ├── image/
│   └── user/
├── uploads/
├── docker-compose.yml
├── Makefile
└── .env


## Environment configuration

The project uses environment variables for the database, application URL and SMTP configuration.

The `.env` file contains secrets and must **not** be committed to Git.

Make sure `.gitignore` contains:

gitignore
.env


### Create the `.env` file

From the project root:


touch .env


Then add:

# Database
DB_HOST=db
DB_PORT=3306
DB_NAME=camagru
DB_USER=camagru
DB_PASSWORD=change_this_database_password
DB_ROOT_PASSWORD=change_this_root_password

# Application
APP_URL=http://localhost:8080

# SMTP
SMTP_HOST=smtp.example.com
SMTP_PORT=587
SMTP_USER=your_smtp_username
SMTP_PASSWORD=your_smtp_password
SMTP_FROM=your_email@example.com


Replace all SMTP placeholder values with the credentials provided by your SMTP provider.

The SMTP server and port must support `STARTTLS`, because the application upgrades the SMTP connection to TLS before authentication.

### Environment variables

| Variable | Description |
| --- | --- |
| `DB_HOST` | MariaDB host. With Docker Compose this is `db`. |
| `DB_PORT` | MariaDB port, normally `3306`. |
| `DB_NAME` | Database name. |
| `DB_USER` | MariaDB application user. |
| `DB_PASSWORD` | Password for the MariaDB application user. |
| `DB_ROOT_PASSWORD` | MariaDB root password used when the container is initialized. |
| `APP_URL` | Base URL used to generate email verification and password-reset links. |
| `SMTP_HOST` | SMTP server hostname. |
| `SMTP_PORT` | SMTP server port. |
| `SMTP_USER` | SMTP authentication username. |
| `SMTP_PASSWORD` | SMTP authentication password. |
| `SMTP_FROM` | Sender email address used by Camagru. |

## Run the project

### Requirements

You need:

- Docker
- Docker Compose

Check that they are available:


docker --version
docker compose version


### Start with the Makefile

From the project root:


make


The Makefile starts the Docker environment used by the project.

### Start directly with Docker Compose

If needed, the project can also be started directly with:


docker compose up --build -d


Docker Compose starts:

- Nginx
- PHP-FPM
- MariaDB

The application is then available at:


http://localhost:8080


The MariaDB database is initialized from `database/schema.sql` when the database volume is created for the first time.

## Stop the project


docker compose down


## Check the containers


docker compose ps


The main services should be running:


nginx
server-php
db


## Important note about `.env`

Never push the real `.env` file to Git because it contains database and SMTP credentials.

A safe approach is to keep only an example file in the repository:


.env.example


For example:

DB_HOST=db
DB_PORT=3306
DB_NAME=camagru
DB_USER=camagru
DB_PASSWORD=
DB_ROOT_PASSWORD=

APP_URL=http://localhost:8080

SMTP_HOST=
SMTP_PORT=
SMTP_USER=
SMTP_PASSWORD=
SMTP_FROM=


A new user can then run:


cp .env.example .env


and fill in the required credentials before starting the project.
