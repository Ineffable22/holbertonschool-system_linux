#include "main.h"

void time_format(char *time)
{
        int i = 4, colon = 0;

        for (; colon < 2; i++)
        {
                putchar(time[i]);
                if (time[i + 1] == ':')
                        colon++;
        }
        putchar(32);
}

void rights(mode_t mode)
{
        printf((mode & S_IRUSR) ? "r" : "-");
        printf((mode & S_IWUSR) ? "w" : "-");
        printf((mode & S_IXUSR) ? "x" : "-");
        printf((mode & S_IRGRP) ? "r" : "-");
        printf((mode & S_IWGRP) ? "w" : "-");
        printf((mode & S_IXGRP) ? "x" : "-");
        printf((mode & S_IROTH) ? "r" : "-");
        printf((mode & S_IWOTH) ? "w" : "-");
        printf((mode & S_IXOTH) ? "x" : "-");
}

void types(mode_t mode)
{
        switch (mode & S_IFMT)
        {
        case S_IFREG:
                printf("-");
                break;
        case S_IFDIR:
                printf("d");
                break;
        case S_IFCHR:
                printf("c");
                break;
        case S_IFBLK:
                printf("b");
                break;
        case S_IFIFO:
                printf("p");
                break;
        case S_IFLNK:
                printf("l");
                break;
        case S_IFSOCK:
                printf("s");
                break;
        }
}
