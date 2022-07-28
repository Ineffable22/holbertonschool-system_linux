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

	while (num/=10)
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
void printer(save *safe, char* dt, int end, int c, option *op)
{
	sort *tmp = NULL;
	int bol = 0;
	while (safe)
	{
		if (c > 1)
		{
			if (bol == 1)
				putchar(10);
			printf("%s:\n", (safe->file));
		}
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
		bol = 1;
	}
}