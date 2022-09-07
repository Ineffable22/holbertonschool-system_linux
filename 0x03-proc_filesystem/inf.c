#include <stdio.h>
#include <string.h>
#include <unistd.h>

/**
 * main - Prints Holberton with Dynamic memory
 *
 * Return: -1 if malloc failed. Otherwise 0
 */
int main(void)
{
	int i = 0;
	char *str = NULL;

	/* Dynamic memory */
	str = strdup("Holberton");
	if (str == NULL)
	{
		fprintf(stderr, "Can’t malloc\n");
		return (-1);
	}
	while (i != 10)
	{
		printf("[%d] %s (%p)\n", i, str, &str);
		sleep(1);
		i++;
	}
	return (0);
}
