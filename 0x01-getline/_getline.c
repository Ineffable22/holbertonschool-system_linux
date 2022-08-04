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
	char *p = NULL;
	unsigned int i = 0;

	if (nmemb == 0 || size == 0)
		return (NULL);

	p = malloc(nmemb * size);

	for (i = 0; i < (nmemb * size); i++)
	{
		*(p + i) = 0;
	}
	return (p);
}

/**
 * _free - free a double pointer of integers and chars
 * @sb: sb is a double pointer that stores all the flags in the stream.
 * @b: buff is a double pointer that stores everything read by position.
 * @size: size of double-pointer
 *
 * Return: Nothing.
 */
void _free(int **sb, char **b, int size)
{
	int i = size - 1;

	for (i = size - 1; i >= 0; i--)
	{
		free(sb[i]);
		free(b[i]);
	}
	free(sb);
	free(b);
}

/**
 * _strncpy - copies a string
 * @dest: destination string
 * @src: source string
 * @n: number of bytes to copy
 *
 * Return: pointer to the resulting string
 */
char *_strncpy(char *dest, char *src, int n)
{
	int i;

	for (i = 0; i < n; i++)
	{
		if (src[i] == 0 && src[i + 1] == 0)
			break;
		dest[i] = src[i];
	}
	while (i < n)
	{
		dest[i] = 0;
		i++;
	}
	return (dest);
}

/**
 * create_stream - Create a getline stream per fp
 * @pos: is the position that depends on the file descriptor.
 * @sb: sb is a double pointer that stores all the flags in the stream.
 * @buff: buff is a double pointer that stores everything read by position.
 * @line: Is a pointer to the line read from the buffer.
 *
 * Return: Line with dynamic memory.
 */
char **create_stream(int pos, int **sb, char **buff, char **line)
{
	/**
	 * sb[pos][0] = open;
	 * sb[pos][1] = door;
	 * sb[pos][2] = last;
	 * sb[pos][3] = fd;
	 */
	int rd = 0, end = 1;

	if (sb[pos][1] == 0)
	{
		rd = read(sb[pos][3], buff[pos], READ_SIZE);
		if (rd == -1)
		{
			return (NULL);
		}
		sb[pos][1] = 1;
	}
	if (sb[pos][1] == 1)
	{
		for (; sb[pos][0] < READ_SIZE; sb[pos][0]++)
		{
			if (buff[pos][sb[pos][0]] == '\n')
			{
				sb[pos][0] += 1;
				break;
			}
			if (buff[pos][sb[pos][0]] == '\0' && buff[pos][sb[pos][0] + 1] == '\0')
			{
				sb[pos][1] = 2;
				end = 0;
				break;
			}
		}
		if (sb[pos][0] == READ_SIZE)
			return (buff);
		*line = _calloc((sb[pos][0] - sb[pos][2]), sizeof(char));
		_strncpy(*line, &buff[pos][sb[pos][2]], ((sb[pos][0] - sb[pos][2]) - end));
		sb[pos][2] = sb[pos][0];
	}
	return (buff);
}

/**
 * validate - Validate if the same fd exists in sb
 * @sb: sb is a double pointer that stores all the flags in the stream.
 * @size: size of double-pointer of integers
 * @fd: is the file descriptor to read
 *
 * Return: a position of fd in sb.
 */
int validate(int **sb, int *size, int fd)
{
	int i = 0;

	for (i = 0; i < *size; i++)
	{
		if (sb[i][3] == fd)
			return (i);
	}
	return (i);
}

/**
 * _getline - Reads an entire line from a file descriptor
 * @fd: is the file descriptor to read
 *
 * Return: If there are no more lines to return, or if there is an error,
 * the function should return NULL
 */
char *_getline(const int fd)
{
	static int **supabuffa;
	/* sp[0][0] = open, sp[0][1] = door, sp[0][2] = last, sp[0][3] = fd */
	static char **buff;
	static int size;
	char *line = NULL;
	int pos = 0;

	if (fd == -1)
	{
		_free(supabuffa, buff, size);
		size = 0;
		return (NULL);
	}
	if (size == 0)
	{
		supabuffa = malloc(sizeof(int *) * 1);
		supabuffa[0] = malloc(sizeof(int) * 4);
		supabuffa[0][0] = 0, supabuffa[0][1] = 0;
		supabuffa[0][2] = 0, supabuffa[0][3] = fd;
		buff = _calloc(1, sizeof(char *));
		buff[0] = _calloc(READ_SIZE + 1, sizeof(char));
		size = 1;
	}
	else
	{
		pos = validate(supabuffa, &size, fd);
		if (pos == size)
		{
			supabuffa = realloc(supabuffa, sizeof(int *) * (size + 1));
			supabuffa[size] = malloc(sizeof(int) * 4);
			supabuffa[size][0] = 0, supabuffa[size][1] = 0;
			supabuffa[size][2] = 0,	supabuffa[size][3] = fd;
			buff = realloc(buff, sizeof(char *) * (size + 1));
			buff[size] = _calloc(READ_SIZE + 1, sizeof(char));
			size += 1;
		}
	}
	buff = create_stream(pos, supabuffa, buff, &line);
	return (line);
}
