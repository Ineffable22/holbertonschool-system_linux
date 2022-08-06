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

	if (tmp && fd == -1)
	{
		while (tmp)
		{
			prev = tmp;
			tmp = tmp->next;
			if (prev->buff)
				free(prev->buff);
			if (prev->data)
				free(prev->data);
			if (prev)
				free(prev), prev = NULL;
		}
		sb = NULL;
	}
	if (tmp && fd != -1)
	{
		while (tmp->data[3] != fd)
		{
			prev = tmp;
			tmp = tmp->next;
		}
		if (tmp->data[3] != fd)
			return (NULL);
		if (prev == NULL)
		{
			prev = tmp, tmp = tmp->next;
			free(prev->buff), free(prev->data), free(prev), prev = NULL;
			sb = tmp;
		}
		else
		{
			if (tmp->next)
				prev->next = tmp->next;
			free(tmp->buff), free(tmp->data), free(tmp), prev->next = NULL;
		}
	}
	return (sb);
}

/**
 * create_stream - Create a getline stream per fp
 * @sb: sb is a pointer to structure that stores all the flags in the stream.
 * @line: Is a pointer to the line read from the buffer.
 * @fd: Is the file descriptor to read
 * @rd: Variable that informs if the reading fails
 *
 * Return: Line with dynamic memory.
 */
supabuffa *create_stream(supabuffa *sb, char **line, int fd, int *rd)
{
	int end = 0;
	supabuffa *tmp = sb;

	if (sb == NULL)
		return (NULL);
	while (tmp->data[3] != fd)
	{
		tmp = tmp->next;
	}
	if (tmp->data[1] == 0)
	{
		*rd = read(tmp->data[3], tmp->buff, READ_SIZE);
		if (*rd == -1)
			return (sb);
		*rd = 0;
		tmp->data[1] = 1;
	}
	if (tmp->data[1] == 1)
	{
		for (; tmp->data[0] < READ_SIZE; tmp->data[0]++)
		{
			if (tmp->buff[tmp->data[0]] == '\n')
			{
				end = 1;
				tmp->data[0] += 1;
				break;
			}
		}
		if ((tmp->data[0] ==  READ_SIZE && tmp->data[2] == READ_SIZE) ||
		(tmp->buff[tmp->data[2]] == '\0' && tmp->data[0] ==  READ_SIZE))
			return (sb);
		*line = _calloc((tmp->data[0] - tmp->data[2]) + 1, sizeof(char));
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
int validate(supabuffa **sb, int fd)
{
	supabuffa *tmp = NULL, *prev = NULL, *node = NULL;

	tmp = *sb;
	while (tmp)
	{
		if (tmp->data[3] == fd)
			return (0);
		prev = tmp;
		tmp = tmp->next;
	}
	node = _calloc(1, sizeof(supabuffa));
	if (node == NULL)
		return (fd);
	node->buff = _calloc(READ_SIZE, sizeof(char));
	if (node->buff == NULL)
		return (fd);
	node->data = malloc(sizeof(int) * 4);
	if (node->data == NULL)
		return (fd);
	node->data[0] = 0;
	node->data[1] = 0;
	node->data[2] = 0;
	node->data[3] = fd;
	node->next = NULL;
	prev->next = node;
	return (0);
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
	int rd = 0;

	if (READ_SIZE < 0)
		return (NULL);
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
				free(sb), sb = NULL, return (NULL);
			}
			sb->data = malloc(sizeof(int) * 4);
			if (sb->data == NULL)
			{
				free(sb->buff), free(sb);
				return (NULL);
			}
			sb->data[0] = 0, sb->data[1] = 0, sb->data[2] = 0, sb->data[3] = fd;
		}
		else
			rd = validate(&sb, fd);
		if (rd == 0)
			sb = create_stream(sb, &line, fd, &rd);
		if (rd == -1)
		{
			sb = _free(sb, rd);
			return (line);
		}
	}
	if (fd == -1 || line == NULL)
		sb = _free(sb, fd);
	return (line);
}
