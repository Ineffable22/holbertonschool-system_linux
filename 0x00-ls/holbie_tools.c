#include "main.h"

/**
 * _strlen - returns the length of a string.
 * @s: string to evaluate
 * Return: the length of the string
 */
int _strlen(char *s)
{
	int x;

	x = 0;
	while (s[x] != '\0')
		x++;
	return (x);
}

/**
 * *_strcpy - copies the string pointed to by src
 * including the terminating null byte (\0)
 * to the buffer pointed to by dest
 * @dest: pointer to the buffer in which we copy the string
 * @src: string to be copied
 *
 * Return: the pointer to dest
 */
char *_strcpy(char *dest, char *src)
{
	int n, i;

	n = 0;
	while (src[n] != 0)
	{
		n++;
	}
	for (i = 0; i < n; i++)
		dest[i] = src[i];
	dest[i] = 0;
	return (dest);
}

/**
 * _strcmp - compares two strings
 * @s1: first string to compare
 * @s2: second string to compare
 *
 * Return: less than 0 if s1 is less than s2, 0 if they're equal,
 * more than 0 if s1 is greater than s2
 */
int _strcmp(char *s1, char *s2)
{
	while (*s1 == *s2)
	{
		if (*s1 == 0)
		{
			return (0);
		}
		s1++;
		s2++;
	}
	return (*s1 - *s2);
}

/**
 * *_strdup - copies the string given as parameter
 * @str: string to duplicate
 *
 * Return: pointer to the copied string (Success), NULL (Error)
 */
char *_strdup(char *str)
{
	char *p;
	int i;

	if (str == 0)
		return (NULL);

	for (i = 0; *(str + i) != 0; i++)
	{}

	p = malloc(sizeof(char) * i + 1);

	if (p == NULL)
		return (0);

	for (i = 0;  *(str + i) != 0; i++)
		*(p + i) = *(str + i);

	*(p + i) = 0;
	return (p);
}

/**
 * *_calloc - allocates memory for an array
 * @nmemb: number of elements in the array
 * @size: size of each element
 *
 * Return: pointer to allocated memory
 */
void *_calloc(unsigned int nmemb, unsigned int size)
{
	char *p;
	unsigned int i;

	if (nmemb == 0 || size == 0)
		return (NULL);

	p = malloc(nmemb * size);

	if (p == NULL)
		return (NULL);

	for (i = 0; i < (nmemb * size); i++)
	{
		*(p + i) = 0;
	}
	return (p);
}
