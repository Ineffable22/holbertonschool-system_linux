#include "main.h"

/**
 * main - Creates ls shell command
 * @argc: number of arguments
 * @argv: double pointer with arguments
 *
 * Return: always 0 if success
 */
int main(int argc, char **argv)
{
	int i = 1, len = 0;
	char *flags = NULL;
	int option = 0;
	int count = 0;
	int res = 0;
	(void) argc;

	while (argv[i])
	{
		if (*argv[i] == '-' && *(argv[i] + 1) != '\0')
		{
			flags = realloc(flags, len  + (_strlen(argv[i])));
			_strcpy(&flags[len], &(*(argv[i] + 1)));
			len = _strlen(flags);
			option = 1;
		}
		else
			count++;
		i++;
	}
	if (option == 1)
		validate(flags);
	res = validate_weight(argv, flags, count);
	if (option == 1)
		free(flags);
	return (res);
}

/**
 * validate - Validator with ls options
 * @flags: string with options to validate
 *
 * Return: Nothing
 */
void validate(char *flags)
{
	char buf[8] = "1aAlrStR";
	int i = 0, j = 0;
	int bol = 0;

	for (i = 0; flags[i]; i++)
	{
		for (j = 0; buf[j]; j++)
		{
			if (flags[i] == buf[j])
			{
				bol = 0;
				break;
			}
			bol = 1;
		}
		if (bol == 1)
		{
			printf("ls: invalid option -- '%c'\n", flags[i]);
			printf("Try 'ls --help' for more information.\n");
			exit(2);
		}
	}
}

/**
 * validate_weight - Compares the weight of the commands
 * with respect to others
 * @argv:  double pointer with arguments
 * @flags: string with options
 * @count: count the number of folders
 *
 * Return: always 0 if success
 */
int validate_weight(char **argv, char *flags, int count)
{
	struct Option *op;
	int i = 0;

	op = malloc(sizeof(option));
	op->hidden = 0;
	op->order = 0;
	op->detail = 0;
	op->recursive = 0;
	for (i = 0; flags && flags[i]; i++)
		switch (flags[i])
		{
		case 'a':
			op->hidden = 1;
			continue;
		case 'A':
			op->hidden = 2;
			continue;
		case 'l':
			op->detail = 2;
			continue;
		case '1':
			if (op->detail == 0)
				op->detail = 1;
			continue;
		case 'r':
			if (op->order == 0)
				op->order = 1;
			continue;
		case 'S':
			op->order = 3;
			continue;
		case 't':
			op->order = 2;
			continue;
		case 'R':
			op->recursive = 1;
			continue;
		}
	i = ls(argv, count, op);
	return (i);
}

/**
 * ls - performs most of the derivation of ls
 * options to other functions
 * @av:  double pointer with arguments
 * @c: count the number of folders
 * @op: pointer to structure with printing options
 *
 * Return: op->err
 */
int ls(char **av, int c, option *op)
{
	DIR *dir = NULL;
	struct Save *safe = NULL;
	int i = 0, end = 0;
	char *dt = NULL;
	int bol = 0;

	op->err = 0;
	if (op->detail == 0)
		dt = "  ", end = 0;
	else
		dt = "\n", end = 1;

	for (i = 1; av[i]; i++)
	{
		if (!(*av[i] == '-' && *(av[i] + 1)))
		{
			bol = 1;
			dir = open_case(dir, av[i], av[0]);
			if (dir == NULL)
			{
				op->err = 2;
				continue;
			}
			safe = create_big_list(safe, av[i], dir, op);
		}
	}
	if (bol == 0)
	{
		dir = open_case(dir, ".", av[0]);
		safe = create_big_list(safe, ".", dir, op);
	}
	printer(safe, dt, end, c, op);
	free_big_list(safe);
	i = op->err;
	free(op);
	return (i);
}

/**
 * open_case - opendir function error handling
 * @dir: pointer to directory
 * @av: double pointer with arguments
 * @hls: executable name
 *
 * Return: pointer to the directory if success, otherwise NULL
 */
DIR *open_case(DIR *dir, char *av, char *hls)
{
	errno = 0;

	dir = opendir(av);
	if (dir == NULL)
	{
		switch (errno)
		{
		case ENOENT:
			printf("%s: cannot access '%s': No such file or directory\n", hls, av);
			break;
		case ENOTDIR:
			printf("%s: cannot access '%s': Not a directory\n", hls, av);
			break;
		case EACCES:
			printf("%s: cannot open directory '%s': Permission denied\n", hls, av);
			break;
		}
		return (NULL);
	}
	return (dir);
}
