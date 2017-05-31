/**
 *class for get db session
 */
#ifndef DBS_H
#define DBS_H

#include "common.h"
#include <mysql/mysql.h>


class DBS
{
  private:
    char *db_name;
    char *db_user;
    char *db_host;
    char *db_passwd;
    int db_port;

    MYSQL *mysql;
    MYSQL_RES *result;

  public:
    /*methods */
    DBS(char *user, char *passwd, char *dbname);
    ~DBS();
    char *get_db_name() {return db_name; };

    int init_database();
    int sql_query(const char *query);
    int count_rows();
    long last_time();
};

#endif
