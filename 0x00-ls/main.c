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
			flags = _realloc(flags, len  + (_strlen(argv[i])));
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
			free(flags);
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
	int i = 0, bol = 0;

	op->file = NULL, op->exe = av[0], op->err = 0, op->type = 1;
	op->size_file = 0, op->output = 0;
	for (i = 1; av[i]; i++)
	{
		if (!(*av[i] == '-' && *(av[i] + 1)))
		{
			bol = 1;
			dir = open_case(dir, av[i], op, 0);
			if (dir == NULL)
				continue;
			if (op->err == 1)
			{
				op->type = 0;
				safe = create_big_list(safe, ".", dir, op);
			}
			else
			{
				op->type = 1;
				safe = create_big_list(safe, av[i], dir, op);
			}
			op->err = 0;
		}
	}
	if (bol == 0)
	{
		dir = open_case(dir, ".", op, 0);
		safe = create_big_list(safe, ".", dir, op);
	}
	end_function(safe, c, op);
	i = op->output == 2 ? 2 : 0;
	free(op);
	return (i);
}

/**
 * open_case - opendir function error handling
 * @dir: pointer to directory
 * @av: double pointer with arguments
 * @op: pointer to structure with printing options
 * @r: recursion number
 *
 * Return: pointer to the directory if success, otherwise NULL
 */
DIR *open_case(DIR *dir, char *av, option *op, char r)
{
	errno = 0;
	dir = opendir(av);
	char *folder = NULL;

	op->err = r;
	if (dir == NULL)
	{
		switch (errno)
		{
		case ENOENT:
			fprintf(stderr,
				"%s: cannot access %s: No such file or directory\n", op->exe, av);
			op->output = 2;
			return (NULL);
		case ENOTDIR:
			if (r == 1)
			{
				fprintf(stderr, "%s: cannot access '%s': Not a directory\n", op->exe, av);
				op->output = 2;
				return (NULL);
			}
			folder = adjust_file_folder(av, op);
			dir = open_case(dir, folder, op, 1);
			free(folder);
			if (dir == NULL)
			{
				fprintf(stderr, "%s: cannot access '%s': Not a directory\n", op->exe, av);
				op->output = 2;
				return (NULL);
			}
			break;
		case EACCES:
			fprintf(stderr,
				"%s: cannot open directory %s: Permission denied\n", op->exe, av);
			op->output = 2;
		}
	}
	return (dir);
}
