#include "sha1.h"
#include <string>
#include "bfile.h"


void get_file_ctime(const char *file, char *res)
{
  struct stat fbuf;
  stat(file, &fbuf);
  sprintf(res, "%ld", (long)fbuf.st_ctime);
}

long get_file_mtime(const char *file) 
{
  struct stat fbuf; 
  stat(file, &fbuf); 
  return (long)fbuf.st_mtime;
}

mode_t get_file_mode(const char *file)
{
  struct stat fbuf;
  stat(file, &fbuf);
  return fbuf.st_mode;
}


void copy_file(char *from, char *to, const char *file, mode_t mode)
{
  int fromfd;
  int tofd;
  char tofile[100];
  size_t i;
  char buf[1000];

  if ((fromfd = open(file, O_RDONLY, mode)) < 0) {
    perror("open");
    return;
  }

  strcpy(tofile, to);
  strcat(tofile, file+strlen(from));
  //check dir if exists
  check_dir(tofile, mode);

  tofd = open(tofile, O_WRONLY | O_CREAT | O_TRUNC, mode);
  if (tofd < 0) {
    perror("create");
  }

  while((i = read(fromfd, buf, sizeof(buf))) != 0)
  {
    if (i == (size_t)-1) {
      perror("read");
      exit(1);
    }
    if (write(tofd, buf, i) != i) {
      perror("write");
    }
  }
  close(fromfd);
  close(tofd);
}


void check_dir(const char *file, mode_t mode)
{
  int i, len;
  char str[100];
  strcpy(str, file);
  len = strlen(str);

  for (i=0; i<len; i++)
  {
    if (str[i] == '/')
    {
      str[i] = '\0';
      if (access(str, 0) != 0)
      {
        mkdir(str, mode);
      }
      str[i] = '/';
    }
  }
  return;
}


unsigned int backup_file(char *from, char *to, long jtime, alist *flist)
{
  DIR *dir;
  struct dirent *ptr;
  mode_t mode;

  if ((dir=opendir(from)) == NULL) {
    perror("opendir");
    return 1;
  }

  for (;(ptr=readdir(dir)) != NULL;)
  {
    if (strcmp(ptr->d_name, ".") == 0 || strcmp(ptr->d_name, "..") == 0) {
      continue;
    }
    else if(ptr->d_type == 8)  //file
    {
      long mtime;
      char ctime[10];
      std::string base_a;

      base_a += from;
      base_a += "/";
      base_a += ptr->d_name;
      
      get_file_ctime(base_a.c_str(), ctime);
      mode = get_file_mode(base_a.c_str());
      mtime = get_file_mtime(base_a.c_str());

      if(mtime > jtime)
      {
        printf("File %s added\n", base_a.c_str());
        get_sha1(strdup(ctime), ctime);
        flist->append(strdup(ctime));
        copy_file(FROM, to, base_a.c_str(), mode);
      }
    }
    else if(ptr->d_type == 4)  //dir
    {
      char base_b[100];
      strcpy(base_b, from);
      strcat(base_b, "/");
      strcat(base_b, ptr->d_name);
      backup_file(base_b, to, jtime, flist);
    }
  }
  closedir(dir);
  return 0;
}




#ifdef TEST_PROGRAM

int main()
{
  char file[] = "/home/mendax/tmp/2.c";
  char path[] = "/home/mendax/tmp";
  alist *list = new alist(10);
  char tmp[20] = {0};
  printf("%s\n", get_file_ctime(file, tmp));
  
  memset(tmp, 0, sizeof(tmp));
  get_file_list(path, list);
  for (int i=0; i<list->size(); i++)
  {
    printf("%s\n", (char *)list->get(i));
  }
  
  delete list;
  return 0;
}
#endif
