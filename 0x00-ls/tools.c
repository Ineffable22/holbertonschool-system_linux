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
void printer(save *safe, char *dt, int end, int c, option *op)
{
	sort *tmp = NULL, *del = NULL;
	int bol = 0;

	while (safe)
	{
		if (c > 1)
		{
			if (bol == 1)
				printf("\n");
			printf("%s:\n", (safe->file));
		}
		tmp = safe->h;
		while (tmp)
		{
			del = tmp->next;
			if (type_hidden(op->hidden, tmp) == 1)
			{
				if (op->detail == 2)
					more_detail(tmp, op);
				if (del == NULL && *dt != '\n')
					dt = "";
				printf("%s%s", (tmp)->r, dt);
			}
			(tmp) = ((tmp)->next);
		}
		if (end == 0)
			printf("\n");

		safe = safe->next;
		bol = 1;
	}
}

/**
 * _realloc - reallocates a memory block using malloc and free
 * @ptr: pointer to the memory previsouly allocated by malloc
 * @old_size: size of the allocated memory for ptr
 * @new_size: new size of the new memory block
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