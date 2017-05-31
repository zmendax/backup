#ifndef JCR_H
#define JCR_H

#include "alist.h"
#include "dbs.h"

class JCR
{
  int JId;
  char JType; 
  int JFiles;
  char Stime[20];
  char JDir[50];
  char JFlist[100];

public:
  JCR(char type, char *dir);
  ~JCR();
  void set_Stime(char *stime);
  char *get_Stime();
  void set_JType(char type);
  void set_JFiles(int num);
  void set_JFlist(alist *list);
  void insert_data(char *sql);
  int run_jrecord(DBS *dbs);

};

inline JCR::JCR(char type, char *dir)
{
  this->JType = type;
  strcpy(this->JDir, dir);
}

inline void JCR::set_JType(char type)
{
  this->JType = type;
}

inline JCR::~JCR() {}

inline void JCR::set_JFiles(int num)
{
  this->JFiles = num;
}

#endif

