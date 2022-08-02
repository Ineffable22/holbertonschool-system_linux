#include "_getline.h"

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

/**
 * _getline - Reads an entire line from a file descriptor
 * @fd: is the file descriptor to read from
 *
 * Return: If there are no more lines to return, or if there is an error,
 *  the function should return NULL
 */
char *_getline(const int fd)
{
	static int open, door;
	static int last;
	static char buff[READ_SIZE];
	char *line = NULL;
	int rd = 0, end = 1;

	if (door == 0)
	{
		rd = read(fd, buff, READ_SIZE);
		if (rd == -1)
			return (NULL);
		door = 1;
	}
	if (door == 2)
		return (NULL);
	if (door == 1)
	{
		for (; open < READ_SIZE; open++)
		{
			if (buff[open] == '\n')
			{
				open++;
				break;
			}
			if (buff[open] == '\0')
			{
				door  = 2;
				end = 0;
				break;
			}
		}
		line = _calloc(sizeof(char), ((open - last)));
		strncpy(line, &buff[last], ((open - last) - end));
		last = open;
	}
	return (line);
}
