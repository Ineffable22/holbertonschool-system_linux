#include "main.h"

/**
 * free_big_list - Clean up a big singly linked list recursively
 * @safe: pointer to struct Save with two singly linked list
 *
 * Return: Nothing
 */
void free_big_list(save *safe)
{
	if (safe)
	{
		free_big_list(safe->next);
		if (safe->h)
		{
			free_list(safe->h);
			free(safe->file);
		}
		free(safe);
	}
}

/**
 * free_list - Clean up a big singly linked list recursively
 * @head: pointer to struct Sort with singly linked list
 *
 * Return: void
 */
void free_list(sort *head)
{
	if (head)
	{
		free_list(head->next);
		free(head->r);
		free(head);
	}
}


/**
 * end_function - final function
 * @safe: pointer to struct Save with two singly linked list
 * @c: count the number of folders
 * @op: pointer to struc Option with printing options
 *
 * Return: op->err
 */
void end_function(save *safe, int c, option *op)
{
	save *tmp = safe;
	int val = 0, i = 0;

	val = printer(safe, c, 0, op, val);
	i = val;
	while (tmp && i > 0)
	{
		tmp = tmp->next;
		i--;
	}
	if (val > 1 && c > 1 && op->detail != 2 && tmp)
		printf("\n");
	printer(safe, c, 1, op, val);
	free_big_list(safe);
}
