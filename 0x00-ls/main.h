#ifndef MAIN_H
#define MAIN_H

/* libraries */
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <time.h>
#include <pwd.h>
#include <sys/types.h>
#include <grp.h>
#include <errno.h>
extern int errno;

/* structure */

/**
 * struct Sort - struct Sort with singly linked list
 * @r: File name
 * @st_mode: permission value
 * @st_time: time value
 * @st_size: size value
 * @st_uid: user value
 * @st_gid: group value
 * @st_nlink: hardlink value
 * @type: type of reading
 * @next: Pointer to the next node in the struct Sort
 */
typedef struct Sort
{
	char *r;
	int st_mode;
	long int st_time;
	long int st_size;
	int st_uid;
	int st_gid;
	long int st_nlink;
	char type;
	struct Sort *next;
} sort;

/**
 * struct Save - struct Save with two singly linked list
 * @h: Pointer to struct Sort with singly linked list
 * @file: File name
 * @type: type of reading
 * @next: Pointer to the next node in the struct Save
 */
typedef struct Save
{
	struct Sort *h;
	char *file;
	char type;
	struct Save *next;
} save;

/**
 * struct Option - Printing options
 * @hidden: 0 not visible / 1 visible / 2 visible minus . and ..
 * @order: 0 default / 1 reverse / 2 time / 3 size
 * @detail: 0 column / 1 row / 2 detail
 * @recursive: 0 normal / 1 recursive
 * @size_file: Maximum size of a file in the folder
 * @err: Error reading directory
 * @output: Program output
 * @exe: executable name
 * @file: filename
 * @type: type of reading
 */
typedef struct Option
{
	int hidden;
	int order;
	int detail;
	int recursive;
	long int size_file;
	int err;
	char output;
	char *exe;
	char *file;
	char type;
} option;

/* prototypes */
/* ----- main.c ----- */
void validate(char *flags);
int validate_weight(char **argv, char *flags, int count);
int ls(char **av, int c, option *op);
DIR *open_case(DIR *dir, char *av, option *op, char r);

/* ----- create.c ----- */
save *create_big_list(save *safe, char *av, DIR *dir, option *op);
sort *create_list(char *av, sort *head, DIR *dir, option *op);
sort *add_node(sort *h, char *name, char *av, option *op);

/* ----- detail.c ----- */
void more_detail(sort *head, option *op);
void types(mode_t mode);
void rights(mode_t mode);
void time_format(char *time);
int type_hidden(int h, sort *head);

/* ----- free.c ----- */
void free_big_list(save *safe);
void free_list(sort *head);
void end_function(save *safe, int c, option *op);

/* ----- tools.c ----- */
int count_digit(long int num);
int printer(save *safe, int c, char o, option *op, int val);
char *_strncpy(char *dest, char *src, int n);
char *adjust_file_folder(char *av, option *op);
char *_realloc(char *ptr, int size);

/* ----- sort.c ----- */
sort *sorting(sort *tmp, sort *node, option *op);
sort *reverse_sort(sort *head);
sort *order_2(sort *node, sort *tmp, sort *head);
sort *order_3(sort *node, sort *tmp, sort *head);

/* ----- holbie_tool.c ----- */
int _strlen(char *s);
char *_strcpy(char *dest, char *src);
int _strcmp(char *s1, char *s2);
char *_strdup(char *str);
void *_calloc(unsigned int nmemb, unsigned int size);

save *sorting_save(save *head, save *node);
save *sorting_save_reverse(save *head, save *node);

/*
 * sort* time_sort(sort *head);
 * sort* size_sort(sort *head);
 */

#endif
