#!/bin/bash

mysqldump -uroot -proot backup > "${HOME}/bacula/SQLbackup/new.sql"
