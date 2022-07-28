#ifndef MAIN_H
#define MAIN_H

/* libraries */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <pwd.h>
#include <sys/types.h>
#include <grp.h>
#include <errno.h>
extern int errno;

/* structure */
typedef struct Sort
{
	char *r;
	int st_mode;
	long int st_time;
	long int st_size;
	int st_uid;
	int st_gid;
	long int st_nlink;
	struct Sort *next;
} sort;

typedef struct Save
{
	struct Sort *h;
	struct Save *next;
} save;

/* prototypes */
void validate(char *flags);
int validate_weight(char **argv, char *flags, int count);
void ls(char **av, int h, int o, int d, int r, int c);
void more_detail(sort *head);
void types(mode_t mode);
void rights(mode_t mode);
void time_format(char *time);
sort* create_list(char *av, sort *head, DIR *dir);
sort* reverse_sort(sort *head);
sort* time_sort(sort *head);
sort* size_sort(sort *head);
int type_hidden(int h, sort *head);
sort* add_node(sort *h, char *name, char *av);
DIR* open_case(DIR *dir, char *av);
void free_list(sort *head);
int count_digit(long int num);
void printer(save *safe, char* dt, int d, int h, int end);

#endif
