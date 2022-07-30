#include "main.h"

/**
 * create_big_list - Create a singly linked list that points to another
 * singly linked list
 * @safe: pointer to struct Save with two singly linked list
 * @av: double pointer with arguments
 * @dir: pointer to directory
 * @op: pointer to struc Option with printing options
 *
 * Return: Pointer to struct save
 */
save *create_big_list(save *safe, char *av, DIR *dir, option *op)
{
	save *tmp = NULL, *current = safe;

	op->size_file = 0;
	tmp = _calloc(sizeof(save), 1);
	if (tmp == NULL)
		return (NULL);
	tmp->h = NULL;
	tmp->h = create_list(av, tmp->h, dir, op);
	tmp->file = _strdup(av);
	tmp->type = op->type;
	if (op->order == 1)
		tmp->h = reverse_sort(tmp->h);

	if (safe == NULL)
	{
		safe = tmp;
		return (tmp);
	}
	while (current->next)
		current = current->next;

	current->next = tmp;

	return (safe);
}

/**
 * create_list - Create a singly linked list
 * @av: double pointer with arguments
 * @head: pointer to struct Sort with singly linked list
 * @dir: pointer to directory
 * @op: pointer to struc Option with printing options
 *
 * Return: Pointer to struct sort
 */
sort *create_list(char *av, sort *head, DIR *dir, option *op)
{
	struct dirent *read = NULL;

	while ((read = readdir(dir)) != NULL)
	{
		if (op->file == NULL)
			head = add_node(head, read->d_name, av, op);
		else
			if (!_strcmp(op->file, read->d_name))
				head = add_node(head, read->d_name, av, op);
	}
	op->file = NULL;
	closedir(dir);
	return (head);
}

char *adjust_file_folder(char *av, option *op)
{
	int i = _strlen(av);
	char *folder = NULL;

	for (; av[i]; i--)
	{
		while (av[i] && av[i] == '/')
		{
			if (av[i] == '/' && av[i + 1] == '/')
			{
				i--;
				continue;
			}
			i++;
			folder = malloc(sizeof(char) * (i + 1));
			_strncpy(folder, av, i);
			op->file = &av[i - 1];
			return (folder);
		}
	}
	folder = malloc(sizeof(char) * 2);
	_strcpy(folder, ".");
	op->file = av;
	return (folder);
}

/**
 * _strncpy - copies a string
 * @dest: destination string
 * @src: source string
 * @n: number of bytes to copy
 *
 * Return: pointer to the resulting string
 */
char *_strncpy(char *dest, char *src, int n)
{
	int i;

	for (i = 0; i < n && src[i] != 0; i++)
		dest[i] = src[i];
	while (i < n)
	{
		dest[i] = 0;
		i++;
	}
	return (dest);
}


/**
 * add_node - Creates nodes, store data and send to sort
 * @head: pointer to struct Sort with singly linked list
 * @name: file name
 * @av: double pointer with arguments
 * @op: pointer to struc Option with printing options
 *
 * Return: Pointer to struct sort
 */
sort *add_node(sort *head, char *name, char *av, option *op)
{
	struct stat buf;
	char *path = NULL;
	sort *node = NULL;

	node = _calloc(sizeof(sort), 1);
	if (node == NULL)
		return (NULL);

	node->r = _calloc(sizeof(char), _strlen(name) + 1);
	if (node->r == NULL)
		return (NULL);
	_strcpy(node->r, name);
	path = _calloc(sizeof(char), _strlen(av) + _strlen(name) + 2);
	_strcpy(path, av);
	_strcpy(&path[_strlen(av)], "/");
	_strcpy(&path[_strlen(av) + 1], name);
	lstat(path, &buf);
	free(path);
	node->st_mode = buf.st_mode;
	node->st_time = buf.st_mtime;
	node->st_size = buf.st_size;
	node->st_uid = buf.st_uid;
	node->st_gid = buf.st_gid;
	node->st_nlink = buf.st_nlink;

	if (buf.st_size > op->size_file)
		op->size_file = buf.st_size;
	if (head == NULL)
	{
		head = node;
		return (head);
	}
	head = sorting(head, node, op);

	return (head);
}
