#include "jcr.h"
#include "bfile.h"
#include "diff.h"
#include "backup.h"

void file_inc(char *from, char *to)
{
  printf("Running Jobs:\n");
  alist *list = new alist(10);
  JCR *jcr = new JCR('I', from);
  DBS *dbs = new DBS(DB_USER, DB_PASSWD, DB_NAME);
  dbs->init_database();

  start_time = NULL;
  time(&start_time);
  // full backup
  if (dbs->count_rows() == 0)
  {
    jcr->set_JType('F');
    backup_file(from, to, FULL_TIME, list);
  }
  // increment backup
  else
  {
    backup_file(from, to, dbs->last_time(), list);
  }

  end_time = NULL;
  time(&end_time);
  printf("This Job takes %ld ms\n", (end_time-start_time));

  jcr->set_JFlist(list);
  if (list->size() <= 0)
  {
  	printf("No file needs to be backed up\n");
  }
  else if (jcr->run_jrecord(dbs) == 0)
  {
  	printf("Finished\n");
  }
  delete list;
  delete jcr;
  delete dbs;
}

void db_inc()
{
  start_time = NULL;
  time(&start_time);

  if (access(FULL_DATA, 0) != 0)
  {
    printf("%s\n", FULL_DATA);
    printf("Create old data and copy full data to directory RESTORE.\n");
    run_script(INIT_SCRIPT);
  }
  else
  {
    run_script(EXPORT_SCRIPT);
    printf("Caculating diff data between old.sql and new.sql\n");
    diff(OLD_DATA, NEW_DATA);
    rename(NEW_DATA, OLD_DATA);
  }
  end_time = NULL;
  time(&end_time);
  printf("This Job takes %ld ms\n", (end_time-start_time));
  printf("Finished\n");
}


int main(int argc, char *argv[])
{
  int ch = 0;
  char from[] = FROM;
  char to[] = TO;

  char tips[1024] = "Connecting to backup system OK\n\
Version 0.1 (10 May 2017)\n\
Defined Jobs:\n\
1: The Job of backing up file data\n\
2: The Job of backing up DB data\n\
Select the Job type (1-2):";

  printf("%s", tips);
  scanf("%d", &ch);

  if (ch == 1)
  {
  	file_inc(from, to);
  } else if (ch == 2)
  {
    db_inc();
  }
  return 0;
}
