#include "main.h"

/**
 * more_detail - Derives information to other functions to
 * get print details from ls
 * @head: pointer to struct Sort with singly linked list
 * @op: pointer to struc Option with printing options
 * Return: Nothing
 */
void more_detail(sort *head, option *op)
{
	char *time;
	struct passwd *usr;
	struct group *grp;
	int i = 0, j = 0;

	types(head->st_mode);
	rights(head->st_mode);
	printf(" %ld", head->st_nlink);
	usr = getpwuid(head->st_uid);
	grp = getgrgid(head->st_gid);
	printf(" %s %s ", usr->pw_name, grp->gr_name);
	time = ctime(&(head->st_time));
	i = count_digit(head->st_size);
	j = count_digit(op->size_file);
	while (j > i)
	{
		printf(" ");
		j--;
	}
	printf("%ld ", head->st_size);
	time_format(time);
}

/**
 * rights - Valid file permissions and prints
 * @mode: Variable that validates permissions S_IRUSR
 *
 * Return: Nothing
 */
void rights(mode_t mode)
{
	printf((mode & S_IRUSR) ? "r" : "-");
	printf((mode & S_IWUSR) ? "w" : "-");
	printf((mode & S_IXUSR) ? "x" : "-");
	printf((mode & S_IRGRP) ? "r" : "-");
	printf((mode & S_IWGRP) ? "w" : "-");
	printf((mode & S_IXGRP) ? "x" : "-");
	printf((mode & S_IROTH) ? "r" : "-");
	printf((mode & S_IWOTH) ? "w" : "-");
	printf((mode & S_IXOTH) ? "x" : "-");
}

/**
 * types - Valid file permissions and prints
 * @mode: Variable that validates permissions S_IFMT
 *
 * Return: Nothing
 */
void types(mode_t mode)
{
	switch (mode & S_IFMT)
	{
	case S_IFREG:
		printf("-");
		break;
	case S_IFDIR:
		printf("d");
		break;
	case S_IFCHR:
		printf("c");
		break;
	case S_IFBLK:
		printf("b");
		break;
	case S_IFIFO:
		printf("p");
		break;
	case S_IFLNK:
		printf("l");
		break;
	case S_IFSOCK:
		printf("s");
		break;
	}
}

/**
 * time_format - Prints the time from the file in a
 * required format
 * @time: Variable with time of last modification
 *
 * Return: Nothing
 */
void time_format(char *time)
{
	int i = 4, colon = 0;

	for (; colon < 2; i++)
	{
		printf("%c", time[i]);
		if (time[i + 1] == ':')
			colon++;
	}
	printf(" ");
}

/**
 * type_hidden - Check if hidden files print
 * @h: Variable with flag to validate
 * @head: pointer to struct Sort with singly linked list
 *
 * Return: 0 if h is 0 or 2, otherwise 1
 */
int type_hidden(int h, sort *head)
{
	if (h == 0)
	{
		if ((head->r)[0] == '.')
			return (0);
	}
	else if (h == 2)
	{
		if (((head->r)[0] == '.' && (head->r)[1] == '\0')
			|| ((head->r)[0] == '.' && (head->r)[1] == '.'))
			return (0);
	}
	return (1);
}
