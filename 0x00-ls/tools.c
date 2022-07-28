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
	sort *tmp = NULL;
	int bol = 0;
	char *del = "";
	int flag = 0;

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
			if (type_hidden(op->hidden, tmp) == 1)
			{
				if (op->detail == 2)
					more_detail(tmp, op);
				if (flag == 1)
					del = dt;
				flag = 1;
				printf("%s%s", del, (tmp)->r);
			}
			(tmp) = ((tmp)->next);
		}
		if (end == 0)
			printf("\n");
		safe = safe->next;
		bol = 1;
	}
}
