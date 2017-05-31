#ifndef B_FILE
#define B_FILE

#include "alist.h"

/* get the st_ctime of a single file */
void get_file_ctime(const char *file, char *res);


/* get file last modify time */
long get_file_mtime(const char *file);


mode_t get_file_mode(const char *file);


/*check if the dir exists or not */
void check_dir(const char *file, mode_t mode);


void copy_file(char *from, char *to, const char *file, mode_t mode);


/* traverse the directory backup incremental file */
unsigned int backup_file(char *from, char *to, long jtime, alist *flist);


#endif
