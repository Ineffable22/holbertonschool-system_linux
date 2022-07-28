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
		//printf("DATA _-~> %s\n", (safe->h));
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