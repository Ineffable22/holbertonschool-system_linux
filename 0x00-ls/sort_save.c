#include "main.h"

/**
 * sorting_save - Creates nodes, store data and send to sort
 * @head: pointer to struct save with singly linked list
 * @node: node to insert into a singly linked list
 *
 * Return: Pointer to struct sort
 */
save *sorting_save(save *head, save *node)
{
	save *tmp = head, *prev = NULL;
	char *name = node->file;

	if (node->file[0] == '.' && node->file[1] == '\0')
		name = node->h->r;
	while (tmp->next && _strcmp(name, tmp->file) >= 0)
	{
		prev = tmp;
		(tmp) = (tmp)->next;
	}
	if (prev)
	{
		prev->next = node;
		node->next = tmp;
	}
	else if (_strcmp(name, tmp->file) > 0)
	{
		tmp->next = node;
		node->next = NULL;
	}
	else
	{
		node->next = head;
		head = node;
	}
	return (head);
}


/**
 * sorting_save_reverse - Creates nodes, store data and send to sort
 * @head: pointer to struct save with singly linked list
 * @node: node to insert into a singly linked list
 *
 * Return: Pointer to struct sort
 */
save *sorting_save_reverse(save *head, save *node)
{
	save *tmp = head, *prev = NULL;
	char *name = node->file;

	if (node->file[0] == '.' && node->file[1] == '\0')
		name = node->h->r;

	while (tmp->next && (_strcmp(name, tmp->file) <= 0))
	{
		prev = tmp;
		(tmp) = (tmp)->next;
	}
	if (prev)
	{
		prev->next = node;
		node->next = tmp;
	}
	else
	{
		node->next = tmp;
		head = node;
	}
	return (head);
}
