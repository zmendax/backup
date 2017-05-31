#include "jcr.h"

void JCR::insert_data(char *sql)
{
  char tmp[10] = {'\0'};
  strcat(sql, "'");
  tmp[0] = this->JType;
  strcat(sql, tmp);
  strcat(sql, "',");
  memset(tmp, 0, sizeof(tmp));
  sprintf(tmp, "%d", this->JFiles);
  strcat(sql, tmp);
  strcat(sql, ",'");
  strcat(sql, this->JDir);
  strcat(sql, "','");
  strcat(sql, this->JFlist);
  strcat(sql, "')");
}

void JCR::set_JFlist(alist *list)
{
  char res[100];
  list->convert_string(list, res);
  strcpy(this->JFlist, res);

  this->set_JFiles(list->size());
}

int JCR::run_jrecord(DBS *dbs)
{
  int res = 0;
  char sql[200] = "insert into JRecord(JType, JFiles, JDir, JFlist) values(";
  insert_data(sql);
  res = dbs->sql_query(sql);
  return res;
}

