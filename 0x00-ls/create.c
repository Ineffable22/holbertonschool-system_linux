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
	(void) op;
	tmp = calloc(sizeof(save), 1);
	if (tmp == NULL)
		return (NULL);
	tmp->h = NULL;
	tmp->h = create_list(av, tmp->h, dir, op);
	tmp->file = strdup(av);

	if (safe == NULL)
	{
		safe = tmp;
		return (tmp);
	}
	while (current->next)
	{
		current = current->next;
	}
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
	struct dirent *read;

	op->size_file = 0;
	while ((read = readdir(dir)) != NULL)
	{
		head = add_node(head, read->d_name, av, op);
	}
	closedir(dir);
	return (head);
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
