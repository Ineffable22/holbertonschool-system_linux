#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#include "_getline.h"

/**
 * main - entry point.
 *
 * Return: always 0.
 */
int main(int argc, char **argv)
{
    int fd = 0, i = 0;
    char *line = NULL;
    (void) argc;
    fd = open(argv[1], O_RDONLY);

    while ((line = _getline(fd)))
    {
        printf("%s", line);
        putchar(10);
        free(line);
        if (i == 5)
            break;
        i++;
    }
    i = 0;
    while ((line = _getline(fd)))
    {
        printf("%s", line);
        putchar(10);
        free(line);
        if (i == 5)
            break;
        i++;
    }

    close(fd);
    _getline(-1);
    return (0);
}
