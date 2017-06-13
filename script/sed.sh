sed -i 's/),/);\n/g' ~/bacula/SQLbackup/new.sql
sed -i 's/^(/INSERT INTO `employees` VALUES (/g' ~/bacula/SQLbackup/new.sql