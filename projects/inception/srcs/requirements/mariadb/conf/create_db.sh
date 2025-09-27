#!/bin/sh

if [ ! -d "/var/lib/mysql/mysql" ]; then

        mysql_install_db --user=mysql --datadir=/var/lib/mysql

fi

if [ ! -d "/var/lib/mysql/wordpress" ]; then

        cat << EOF > /tmp/create_db.sql
USE mysql;
FLUSH PRIVILEGES;
DELETE FROM     mysql.user WHERE User='';
DROP DATABASE test;
DELETE FROM mysql.db WHERE Db='test';
DELETE FROM mysql.user WHERE User='root' AND Host NOT IN ('localhost', '127.0.0.1', '::1');
ALTER USER 'root'@'localhost' IDENTIFIED BY '${DB_ROOT}';
CREATE DATABASE ${DB_NAME};
CREATE USER '${DB_USER}'@'%' IDENTIFIED by '${DB_PASS}';
GRANT ALL PRIVILEGES ON ${DB_NAME}.* TO '${DB_USER}'@'%';
FLUSH PRIVILEGES;
EOF
        /usr/bin/mysqld --user=mysql --bootstrap < /tmp/create_db.sql
        rm -f /tmp/create_db.sql
fi
exec /usr/bin/mysqld --user=mysql --console
