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
 * _free - free a pointer to structure
 * @sb: sb is a pointer to structure that stores all the flags in the stream.
 * @fd: Is the file descriptor to read
 *
 * Return: Nothing.
 */
supabuffa *_free(supabuffa *sb, int fd)
{
	supabuffa *prev = NULL, *tmp = sb;

	if (sb && fd == -1)
	{
		while (sb)
		{
			prev = sb;
			sb = sb->next;
			free(prev->buff);
			free(prev->data);
			free(prev);
		}
	}
	if (fd != -1)
	{
		while (tmp->data[3] != fd)
		{
			prev = tmp;
			tmp = tmp->next;
		}
		if (prev == NULL)
		{
			prev = tmp;
			tmp = tmp->next;
			free(prev->buff);
			free(sb->data);
			free(prev);
			return (tmp);
		}
		else
		{
			if (tmp->next)
				prev->next = tmp->next;
			free(tmp->buff);
			free(sb->data);
			free(tmp);
		}
	}
	return (sb);
}

/**
 * create_stream - Create a getline stream per fp
 * @sb: sb is a pointer to structure that stores all the flags in the stream.
 * @line: Is a pointer to the line read from the buffer.
 * @fd: Is the file descriptor to read
 *
 * Return: Line with dynamic memory.
 */
supabuffa *create_stream(supabuffa *sb, char **line, int fd)
{
	int rd = 0, end = 1;
	supabuffa *tmp = sb;

	while (tmp->data[3] != fd)
		tmp = tmp->next;
	if (tmp->data[1] == 0)
	{
		rd = read(tmp->data[3], tmp->buff, READ_SIZE);
		if (rd == -1)
			exit(-1);
		tmp->data[1] = 1;
	}
	if (tmp->data[1] == 1)
	{
		for (; tmp->data[0] < READ_SIZE; tmp->data[0]++)
		{
			if (tmp->buff[tmp->data[0]] == '\n')
			{
				tmp->data[0] += 1;
				break;
			}
			if (tmp->buff[tmp->data[0]] == '\0' && tmp->buff[tmp->data[0] + 1] == '\0')
			{
				tmp->data[1] = 2, end = 0;
				break;
			}
		}
		if (tmp->data[0] == READ_SIZE)
			return (sb);
		*line = _calloc((tmp->data[0] - tmp->data[2]), sizeof(char));
		if (*line == NULL)
		{
			_free(sb, -1);
			return (NULL);
		}
		memcpy(*line, &tmp->buff[tmp->data[2]],
		((tmp->data[0] - tmp->data[2]) - end));
		tmp->data[2] = tmp->data[0];
	}
	return (sb);
}

/**
 * validate - Validate if the same fd exists in sb
 * @sb: sb is a pointer to structure that stores all the flags in the stream.
 * @fd: Is the file descriptor to read
 *
 * Return: a position of fd in sb.
 */
supabuffa *validate(supabuffa *sb, int fd)
{
	supabuffa *tmp = sb, *prev = NULL, *node = NULL;

	while (tmp)
	{
		if (tmp->data[3] == fd)
			return (sb);
		prev = tmp;
		tmp = tmp->next;
	}
	node = _calloc(1, sizeof(supabuffa));
	if (node == NULL)
	{
		_free(sb, -1);
		return (NULL);
	}
	node->buff = _calloc(READ_SIZE, sizeof(char));
	if (node->buff == NULL)
	{
		_free(sb, -1);
		return (NULL);
	}
	node->data = malloc(sizeof(int) * 4);
	node->data[0] = 0;
	node->data[1] = 0;
	node->data[2] = 0;
	node->data[3] = fd;
	node->next = NULL;
	prev->next = node;
	return (sb);
}

/**
 * _getline - Reads an entire line from a file descriptor
 * @fd: Is the file descriptor to read
 *
 * Return: If there are no more lines to return, or if there is an error,
 * the function should return NULL
 */
char *_getline(const int fd)
{
	static supabuffa *sb;
	/* sb[0][0] = open, sb[0][1] = door, sb[0][2] = last, sb[0][3] = fd */
	char *line = NULL;

	if (fd != -1)
	{
		if (!sb)
		{
			sb = _calloc(1, sizeof(supabuffa));
			if (sb == NULL)
				return (NULL);
			sb->buff = _calloc(READ_SIZE, sizeof(char));
			if (sb->buff == NULL)
			{
				free(sb);
				sb = NULL;
				return (NULL);
			}
			sb->data = malloc(sizeof(int) * 4);
			if (sb->data == NULL)
			{
				free(sb->buff);
				free(sb);
				return (NULL);
			}
			sb->data[0] = 0;
			sb->data[1] = 0;
			sb->data[2] = 0;
			sb->data[3] = fd;
		}
		else
			sb = validate(sb, fd);
		sb = create_stream(sb, &line, fd);
	}
	if (fd == -1 || line == NULL)
		sb = _free(sb, fd);
	return (line);
}
