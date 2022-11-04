#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

/**
 * main - Compare 2 files
 *
 * Return: Always 0
 */
int main(void)
{
	char first[BUFSIZ];
	char second[BUFSIZ];
	int fd1 = 0, fd2 = 0, i = 0, rd1 = 0, rd2 = 0;

	fd1 = open("text1", O_RDONLY);
	fd2 = open("text2", O_RDONLY);

	memset(first, 0, BUFSIZ);
	memset(second, 0, BUFSIZ);
	rd1 = read(fd1, first, BUFSIZ);
	rd2 = read(fd2, second, BUFSIZ);
	if (rd1 != rd2)
		printf("The files are not the same size\n");

	while (first[i] == second[i] && first[i] != 0 && second[i] != 0)
		i++;
	printf("i => %d || rd1 => %d || rd2 => %d\n", i, rd1, rd2);
	if (i != rd1)
	{
		printf("FAIL in line (%d)\n", i);
		printf("%s\n", &first[i]);
	}
	else
		printf("OK\n");
	return (0);
}
