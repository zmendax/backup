#ifndef DIFF_H
#define DIFF_H

#ifdef __cplusplus
extern "C" {
#endif

typedef struct s_file
{
	char** lines;
	unsigned int nb_line;
	int* size_line;
} t_file;

FILE *fp;

#define EDIT_FILE "/home/mendax/bacula/SQLrestore/edit"


t_file* file_create(char* file_name);
void file_print(t_file* file);
char* get_line(t_file* file,int index);
t_file * get_lcs(t_file* file_1, t_file* file_2);
t_file * to_lower_case(t_file* file);
int is_file_different(t_file * file1, t_file * file2);
t_file * ignore_blank(t_file * file);
t_file* str_onespace (t_file* file);
t_file* str_onetab(t_file* file);
void file_compare(t_file* file_1, t_file* file_2, t_file* file_1_print, t_file* file_2_print);

void diff(char *file1, char *file2);

#ifdef __cplusplus
}
#endif


#endif /*DIFF_H*/