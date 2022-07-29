#include "main.h"
#include <pwd.h>
#include <sys/types.h>
#include <grp.h>

int main(int argc, char **argv)
{
	DIR *dir;
	struct dirent *read;
	struct stat buf;
	char *path = NULL;
	char *time;
	struct passwd *usr;
	struct group *grp;

	if (argc == 1)
	{
		printf("sin argumentos\n");
		return (0);
	}
	dir = opendir(argv[1]);
	while((read = readdir(dir)) != NULL)
	{
		path = _strdup(argv[1]);
		path = realloc(path, _strlen(path) + _strlen(read->d_name) + 1);
		
		strcat(path, read->d_name);
		lstat(path, &buf);

		types(buf.st_mode);
		rights(buf.st_mode);

		usr = getpwuid(buf.st_uid);
		grp = getgrgid(buf.st_gid);
		printf(" %s %s ", usr->pw_name, grp->gr_name);
		printf("<time %ld>", buf.st_mtime);
		time = ctime(&(buf.st_mtime));
		printf("%ld ", buf.st_size);
		time_format(time);
		printf("%s\n",read->d_name);
		//printf("%d, %ld, %ld, %d, %d, %d\n", buf.st_mode, buf.st_mtime, buf.st_size, buf.st_uid, buf.st_gid, buf.st_nlink);
		free(path);
	}
	closedir(dir);
	return (0);
}

void time_format(char *time)
{
	int i = 4, colon = 0;

	for (; colon < 2; i++)
	{
		putchar(time[i]);
		if (time[i + 1] == ':')
			colon++;
	}
	putchar(32);
}

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
	putchar(32);
}

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
