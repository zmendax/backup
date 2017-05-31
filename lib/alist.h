#ifndef ALIST_H
#define ALIST_H

#include "common.h"

class alist
{
  void **items;
  int num_items;
  int max_items;
  int num_grow;
  int cur_item;
  void grow_list();
public:
  alist(int num = 10);
  ~alist();
  void append(void *item);
  void *remove(int index);
  void *get(int index);
  bool empty() const;
  void *next();
  void *first();
  int size() const;
  void destroy();
  void grow(int num);

  char *convert_string(alist *list, char *res);
};

inline bool alist::empty() const
{
  return num_items == 0;
}

inline alist::alist(int num)
{
  items = NULL;
  num_items = 0;
  max_items = 0;
  num_grow = num;
}

inline alist::~alist()
{
  destroy();
}

inline int alist::size() const
{
  return num_items;
}

inline void alist::grow(int num)
{
  num_grow = num;
}

#endif
