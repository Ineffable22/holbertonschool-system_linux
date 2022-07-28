#include "main.h"

long int size_file = 0;
int main(int argc, char **argv)
{
	int i = 1, len = 0;
	char *flags = NULL;
	int option = 0;
	int count = 0;
	(void) argc;
	/*if (argc == 1)
	  argv[1] = ".";*/
	while (argv[i])
	{
		if (*argv[i] == '-' && *(argv[i] + 1) != '\0')
		{
			flags = realloc(flags, len  + (strlen(argv[i])));
			//printf("->%ld\n", strlen(argv[i]));
			//printf("%ld\n", strlen(flags) + (strlen(argv[i]) - 1));
			strcpy(&flags[len], &(*(argv[i] + 1)));
			len = strlen(flags);
			option = 1;
		}
		else
			count++;
		i++;
	}
	if (option == 1)
		validate(flags);
	//printf("flags => %s\n", flags);
	validate_weight(argv, flags, count);
	if (option == 1)
		free(flags);
	return (0);
}

int validate_weight(char **argv, char *flags, int count)
{
	struct Option *op;
	op = malloc(sizeof(option));
	if (op == NULL)
		return (-1);
	op->hidden = 0; /* 0 no visibles / 1 visibles / 2 visibles menos . .. */
	op->order = 0; /* 0 ningun orden / 1 reverse / 2 time / 3 size */
	op->detail = 0; /* 0 column / 1 row  / 2 detail */
	op->recursive = 0; /* 0 normal / 1 recursive */
	int i = 0;
	if (flags == NULL)
	{
		ls(argv, count, op);
		return (0);
	}
	for (i = 0; flags[i]; i++)
	{
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
	}
	ls(argv, count, op);
	return (0);
}

void ls(char **av, int c, option *op)
{
	DIR *dir = NULL;
	//struct Sort *head = NULL;
	struct Save *safe = NULL;
	int i = 0, end = 0;
	char *dt = NULL;
	if (op->detail == 0)
		dt = "  ", end = 0;
	else
		dt = "\n" , end = 1;

	for (i = 1; av[i]; i++)
	{
		if (*av[i] != '-')
		{
			if ((dir = open_case(dir, av[i])) == NULL)
				continue;
			//printf("DATA -> %s\n", av[i]);
			//printf("dir = %d\n", res_open);
			safe = create_big_list(safe, av[i], dir, op);
			//printf("orden -> %d\n", o);
			/*
			while(head)
			{
				if (type_hidden(h, head) == 1)
				{
					if (d == 2)
						more_detail(head);
					printf("%s%s", head->r, dt);
				}
				head = head->next;
			}
			if (end == 0)
				putchar(10);
			*/

			//free_list(head);

		}
	}
	printer(safe, dt, end, c, op);
	free(op);
	free_big_list(safe);
}
save* create_big_list(save *safe, char *av, DIR *dir, option *op)
{
	save *tmp = NULL, *current = safe;
	//struct Sort *head;
        tmp = calloc(sizeof(save), 1);
	if (tmp == NULL)
		return (NULL);
	//tmp->h = malloc(sizeof(sort));
	//head = tmp->h;
	//head = NULL;
	tmp->h = NULL;
	tmp->h = create_list(av, tmp->h, dir);
	tmp->file = strdup(av);

	if (op->order == 1)
		tmp->h = reverse_sort(tmp->h);
	else if (op->order == 2)
		tmp->h = time_sort(tmp->h);
	else if (op->order == 3)
		tmp->h = size_sort(tmp->h);
	if (safe == NULL)
	{
		safe = tmp;
		return tmp;
	}
	while (current->next)
	{
		current = current->next;
	}
	current->next = tmp;

	return (safe);
}

void printer(save *safe, char* dt, int end, int c, option *op)
{
	sort *tmp = NULL;
	while (safe)
	{
		if (c > 1)
			printf("%s:\n", (safe->file));
		tmp = safe->h;
		while(tmp)
		{
			//printf("value => %s\n", (safe->h)->r);
			if (type_hidden(op->hidden, tmp) == 1)
			{
				if (op->detail == 2)
					more_detail(tmp);
				printf("%s%s", (tmp)->r, dt);
			}
			(tmp) = ((tmp)->next);
		}
		if (end == 0)
			putchar(10);
		safe = safe->next;
	}
}

void free_big_list(save *safe)
{
	if (safe)
	{
		free_big_list(safe->next);
		//printf("DATA _-~> %s\n", (safe->h));
		if (safe->h)
		{
			free_list(safe->h);
			free(safe->file);
		}
		free(safe);
	}
}
void free_list(sort *head)
{
	if (head)
	{
		free_list(head->next);
		free(head->r);
		free(head);
	}
}

DIR* open_case(DIR *dir, char *av)
{
	errno = 0;
	if ((dir = opendir(av)) == NULL)
	{
		switch (errno)
		{
		case ENOTDIR:
			printf("'%s' is not a directory\n", av); break;
		case EACCES:
			printf("Permission denied\n"); break;
		case ENOENT:
			printf("ls: cannot access '%s': No such file or directory\n", av); break;
		}
		return (NULL);
	}
	return (dir);
}

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

sort* create_list(char *av, sort *head, DIR *dir)
{
	struct dirent *read;
	while((read = readdir(dir)) != NULL)
	{
		head = add_node(head, read->d_name, av);
	}
	closedir(dir);
	return head;
}

sort* add_node(sort *head, char *name, char *av)
{
	struct stat buf;
	char *path = NULL;
	sort *node = NULL, *tmp = head;

	node = calloc(sizeof(sort), 1);
	if (node == NULL)
		return (NULL);

	node->r = calloc(sizeof(char), strlen(name) + 1);
	if (node->r == NULL)
		return (NULL);
	strcpy(node->r, name);
	path = calloc(sizeof(char), strlen(av) + strlen(name) + 2);
	strcpy(path, av);
	strcpy(&path[strlen(av)], "/");
	strcpy(&path[strlen(av) + 1], name);
	lstat(path, &buf);
	free(path);
	node->st_mode = buf.st_mode;
	node->st_time = buf.st_mtime;
	node->st_size = buf.st_size;
	node->st_uid = buf.st_uid;
	node->st_gid = buf.st_gid;
	node->st_nlink = buf.st_nlink;
	//head->b = buf;

	if (buf.st_size > size_file)
		size_file = buf.st_size;

	if (head == NULL)
	{
		head = node;
		return (head);
	}
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = node;
	return (head);
}

/**
 * reverse_listint - Reverses a listint_t linked list.
 * @head: pointer to the first element in the linked list
 *
 * Return: a pointer to the first node of the reversed list
 */
sort* reverse_sort(sort *head)
{
	sort *prev = NULL;
	sort *next = NULL;

	while (head)
	{
		next = (head)->next;
		(head)->next = prev;
		prev = head;
		head = next;
	}
	head = prev;
	return (head);
}

sort* time_sort(sort *head)
{
	sort *prev = NULL;
	sort *next = NULL;
	sort *current = head;
	sort *tmp = head;
	int time = 0;
	int next_time = 0;

	while(head)
	{
		time = (head->st_time);
		next_time = ((head->next)->st_time);
		tmp = head;
		while (time > next_time)
		{
			next = tmp->next;
			tmp->next = prev;
			prev = tmp;
			tmp = next;

			tmp = tmp->next;
			time = (tmp->st_time);
			next_time = ((tmp->next)->st_time);
		}
		head = head->next;
	}
	return (current);
}

sort* size_sort(sort *head)
{
	sort *prev = NULL;
	sort *next = NULL;
	sort *current = head;
	sort *tmp = head;
	int time = 0;
	int next_time = 0;

	while(head)
	{
		time = (head->st_size);
		next_time = ((head->next)->st_size);
		tmp = head;
		while (time > next_time)
		{
			next = tmp->next;
			tmp->next = prev;
			prev = tmp;
			tmp = next;

			tmp = tmp->next;
			time = (tmp->st_size);
			next_time = ((tmp->next)->st_size);
		}
		head = head->next;
	}
	return (current);
}


void more_detail(sort *head)
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
	j = count_digit(size_file);
	while (j != i)
	{
		putchar(32);
		j--;
	}
	printf("%ld ", head->st_size);
	time_format(time);
}
int count_digit(long int num)
{
	int i = 1;

	while (num/=10)
		i++;
	return (i);
}

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
