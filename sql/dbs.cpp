#include "dbs.h"

DBS::DBS(char *user, char *passwd, char *dbname)
{
  mysql = NULL;
  db_port = 0;
  db_user = user;
  db_passwd = passwd;
  db_name = dbname;
}

DBS::~DBS()
{
  if (result != NULL) {
    mysql_free_result(result);
  }
  mysql_close(mysql);
}

int DBS::init_database()
{
  MYSQL *con;
  mysql = mysql_init(mysql);
  if (mysql == NULL)
  {
    perror("init database");
    return 1;
  }

  con = mysql_real_connect(mysql,db_host,db_user,db_passwd,
        db_name,db_port,NULL,0);
  if (con == NULL) {
    perror("connect database");
    return mysql_errno(mysql);
  }

  return 0;
}

int DBS::sql_query(const char *query)
{
  printf("[SQL]: %s\n", query);
  // if success return 0
  return mysql_query(mysql, query);
}

int DBS::count_rows()
{
  MYSQL_ROW row;
  char sql[] = "select count(*) from JRecord where JType='F'";
  if (sql_query(sql) == 0)
  {
    result = mysql_store_result(mysql);
    if (!result) {
      return 0;
    }else{
      row = mysql_fetch_row(result);
    }
  }
  return atoi(row[0]);
}

long DBS::last_time()
{
  long jtime = 0L;
  char sql[] = "select * from JRecord order by JId desc limit 1";
  char time_sql[100] = "select UNIX_TIMESTAMP('";
  if (sql_query(sql) == 0)
  {
    result = mysql_store_result(mysql);
    if (result == NULL) {
      return 0;
    } else {
      MYSQL_ROW row;
      row = mysql_fetch_row(result);
      strcat(time_sql, row[3]);
      strcat(time_sql, "')");

      if (sql_query(time_sql) == 0)
      {
        result = mysql_store_result(mysql);
        if(result == NULL) {
          return 0;
        } else {
          MYSQL_ROW row = mysql_fetch_row(result);
          jtime = atol(row[0]); 
        }
      }
    }
  }
  //printf("Last Job Time: %ld\n", jtime);//TODO
  return jtime;
}

#ifdef TEST_PROGRAM

int main()
{
  DBS *dbs = new DBS("backup", "root", "root");
  dbs->init_database();
  printf("%ld\n", dbs->last_time());
  delete dbs;
  return 0;
}
#endif
