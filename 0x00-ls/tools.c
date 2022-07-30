#include "main.h"

/**
 * count_digit - Counts the number of characters in a number
 * @num: number to count
 *
 * Return: number of characters
 */
int count_digit(long int num)
{
	int i = 1;

	while (num /= 10)
		i++;
	return (i);
}

/**
 * printer - Prints the LS output with the chosen option
 * @safe: pointer to struct Save with two singly linked list
 * @dt: separator
 * @end: string indicating how it will end
 * @c: flag reporting the number of folders
 * @op: pointer to struc Option with printing options
 *
 * Return: Nothing
 */
int printer(save *safe, int c, char o, option *op, int val)
{
	sort *tmp = NULL, *del = NULL;
	int bol = 0;

	if (val == 1 && o == 1 && c > 1 && op->detail != 2)
		printf("\n");
	while (safe)
	{
		if (safe->type != o)
			safe = safe->next, continue;
		if ((c > 1 && o == 1))
		{
			if (bol == 1 && op->detail < 2)
				printf("\n");
			if (op->detail == 2)
				printf("\n");
			printf("%s:\n", (safe->file));
		}, tmp = safe->h;
		while (tmp)
		{
			del = tmp->next;
			if (type_hidden(op->hidden, tmp) == 1)
			{
				if (op->detail == 2)
					more_detail(tmp, op);
				printf("%s", (tmp)->r), val = 1;
				if (o == 1 && del != NULL)
					op->detail == 0 ? printf("  ") : printf("\n");
			}
			(tmp) = ((tmp)->next);
		}
		if ((op->detail >= 0 && o == 1 && safe->type == o) ||
		    (op->detail > 0 && o == 0 && safe->type == o))
			printf("\n");
		if (op->detail == 0 && o == 0 && safe->type == o)
			printf("  ");
		safe = safe->next, bol = 1;
	}
	if (op->detail == 0 && o == 0 && val == 1)
		printf("\n");
	return (val);
}

/**
 * _realloc - reallocates a memory block using malloc and free
 * @ptr: pointer to the memory previsouly allocated by malloc
 * @size: new size of the new memory block
 *
 * Return: pointer to the newly allocated memory block
 */
char *_realloc(char *ptr, int size)
{
	char *ptr1 = NULL;

	if (ptr == NULL)
		return (malloc(sizeof(char) * size));
	ptr1 = malloc(sizeof(char) + size + 1);
	ptr1 = _strcpy(ptr1, ptr);
	free(ptr);
	return (ptr1);
}
