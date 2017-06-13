#ifndef BACKUP_H
#define BACKUP_H

#define FULL_TIME 1
#define INIT_SCRIPT "../script/sql_full.sh"
#define EXPORT_SCRIPT "../script/export.sh"
#define SED_SCRIPT "../script/sed.sh"
#define RESTORE_SCRIPT "../script/restore.sh"

#define FULL_DATA "/home/mendax/bacula/SQLbackup/full.sql"
#define OLD_DATA "/home/mendax/bacula/SQLbackup/old.sql"
#define NEW_DATA "/home/mendax/bacula/SQLbackup/new.sql"
#define EDIT_DATA "/home/mendax/bacula/SQLrestore/edit.sql"


time_t start_time;
time_t end_time;

extern void run_script(char *file);

void file_inc(char *from, char *to);

void db_inc();

void db_restore();

#endif