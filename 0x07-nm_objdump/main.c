#include "lib_elf.h"

/**
 * main - Displays the information contained in the ELF file header
 * of an ELF file.
 * @argc: Arguments number
 * @argv: Each argument per pointer
 *
 * Return: 0 if successful, else exit on error
 */
int main(int argc, char **argv)
{
	elf ep;
	int fd = 0;

	if (argc != 2)
	{
		printf("hnm [objfile ...]\n");
		return (-1);
	}
	memset(&ep, 0, sizeof(ep));
	fd = process_ehdr(&ep, argv[1]);
	
	switch_endians(&ep);
	check_elf(&ep);
	symbol_1(&ep, fd, argv[1]);
	symbol_2(&ep);
	close(fd);
	return (0);
}

/**
 * process_ehdr - Malloc pointer and open and read file
 * @ep: Pointer to ELF structure
 * @filename: name of the file to read
 *
 * Return: File descriptor
 */
int process_ehdr(elf *ep, char *filename)
{
	int fd = 0, rd = 0;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		fprintf(stderr, "Can't open the file %s\n", filename);
		exit(98);
	}
	rd = read(fd, &((*ep).eh64), sizeof((*ep).eh64));
	if (rd == -1 || rd != sizeof((*ep).eh64))
	{
		fprintf(stderr, "Can't read the file %s\n", filename);
		exit(98);
	}
	if (!CHECK_64(ep->eh64))
	{
		lseek(fd, 0, SEEK_SET);
		rd = read(fd, &(*ep).eh32, sizeof(ep->eh32));
		if (rd == -1 || rd != sizeof(ep->eh32))
		{
			fprintf(stderr, "Can't read the file %s\n", filename);
			return (-1);
		}
	}
	return (fd);
}

/**
 * check_elf - Checks if file is ELF file
 * @ep: Pointer to ELF structure
 *
 * Return: Nothing
 */
void check_elf(elf *ep)
{
	if (EGET(e_ident[EI_MAG0]) != 0x7f ||
	    EGET(e_ident[EI_MAG1]) != 'E' ||
	    EGET(e_ident[EI_MAG2]) != 'L' ||
	    EGET(e_ident[EI_MAG3]) != 'F')
	{
		printf("Not an ELF file - it has the wrong");
		printf("magic bytes at the start\n");
		exit(1);
	}
}
