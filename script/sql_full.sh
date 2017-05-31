#!/bin/bash

mysqldump -uroot -proot backup > "${HOME}/bacula/SQLbackup/full.sql"

cp "${HOME}/bacula/SQLbackup/full.sql" "${HOME}/bacula/SQLbackup/old.sql"
cp "${HOME}/bacula/SQLbackup/full.sql" "${HOME}/bacula/SQLrestore/full.sql"