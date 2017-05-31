#include "alist.h"

//#define TEST_PROGRAM

void alist::grow_list()
{
  if (items == NULL)
  {
    if (num_grow == 0)
    {
      num_grow = 1;
    }
    items = (void **)malloc(num_grow * sizeof(void *));
    max_items = num_grow;
  }else if (num_items == max_items)
  {
    max_items += num_grow;
    items = (void **)realloc(items, max_items * sizeof(void *));
  }
}

void *alist::first()
{
  cur_item = 1;
  if (num_items == 0) {
    return NULL;
  } else {
    return items[0];
  }
}

void *alist::next()
{
  if (cur_item >= num_items) {
    return NULL;
  } else {
    return items[cur_item++];
  }
}

void alist::append(void *item)
{
  grow_list();
  items[num_items++] = item;
}

void *alist::remove(int index)
{
  void *item;
  if (index < 0 || index >= num_items) {
    return NULL;
  }
  item = items[index];
  num_items--;
  for (int i=index; i<num_items; i++) {
    items[i] = items[i+1];
  }
  return item;
}

void *alist::get(int index)
{
  if (index < 0 || index >= num_items) {
    return NULL;
  }
  return items[index];
}

void alist::destroy()
{
  if (items) {
    for (int i=0; i<num_items; i++) {
      free(items[i]);
      items[i] = NULL;
    }
    free(items);
    items = NULL;
  }
  num_items = 0;
  max_items = 0;
  num_grow = 0;
}

char *alist::convert_string(alist *list, char *res)
{
  memset(res, 0, sizeof(res));
  for (int i=0; i<list->size(); i++)
  {
    strcat(res, (char *)list->get(i));
    if (i == list->size()-1)
      break;
    else
      strcat(res, ",");
  }
  return res;
}


#ifdef TEST_PROGRAM

int main()
{
  alist *flist;
  char buf[30];

  printf("Manual allocation/destruction of list:\n");
  flist = new alist(10);

  for (int i=0; i<20; i++) {
    sprintf(buf, "This is item %d", i);
    flist->append(strdup(buf));
  }
  for (int i=0; i<flist->size(); i++) {
    printf("Item %d = %s\n", i, (char*)flist->get(i));
  }
  delete flist;
}
#endif
