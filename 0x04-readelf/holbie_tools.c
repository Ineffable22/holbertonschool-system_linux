#include "lib_elf.h"

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
 * itoa - Converts a number to a string
 * @val: Number to convert
 * @base: Number base
 *
 * Return: String with number
 */
char *itoa(int val, int base)
{
	static char buf[32] = {0};
	int i = 30;

	for (; val && i ; --i, val /= base)
		buf[i] = "0123456789abcdef"[val % base];

	return (&buf[i + 1]);
}

/**
 * process_ehdr - Malloc pointer and open and read file
 * @eh: Pointer to the ELF header
 * @filename: name of the file to read
 *
 * Return: File descriptor
 */
int process_ehdr(elf *eh, char *filename)
{
	int fd = 0, rd = 0;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		fprintf(stderr, "Can't open the file %s\n", filename);
		exit(98);
	}
	rd = read(fd, &((*eh).eh64), sizeof((*eh).eh64));
	if (rd == -1 || rd != sizeof((*eh).eh64))
	{
		fprintf(stderr, "Can't read the file %s\n", filename);
		exit(98);
	}
	return (fd);
}

