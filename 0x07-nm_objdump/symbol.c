#include "lib_elf.h"

void symbol_1(elf *ep, int fd, char *filename)
{
	int rd = 0;
	int size = EGET(e_shnum) * EGET(e_shentsize);
	char *symbol = NULL;

	symbol = calloc(sizeof(EGET(e_shnum)), size);
	if (symbol == NULL)
	{
		fprintf(stderr, "Can´t Calloc\n");
		exit(1);
	}
	lseek(fd, EGET(e_shoff), SEEK_SET);
	rd = read(fd, symbol, size);
	if (rd == -1)
	{
		fprintf(stderr, "Can't read the file %s\n", filename);
		exit(98);
	}
	if (CHECK_64(ep->eh64))
		ep->sh64 = (Elf64_Shdr *) symbol;
	else
		ep->sh32 = (Elf32_Shdr *) symbol;
}

void symbol_2(elf *ep)
{
	int i = 0;
	char *str;

	str = calloc(1, SGET(EGET(e_shstrndx), sh_size));
	if (!str)
		exit(1);
	lseek(fd, SGET(EGET(e_shstrndx), sh_offset), SEEK_SET);
	read(fd, str, SGET(EGET(e_shstrndx), sh_size));
	for (i = 0; i < EGET(e_shnum); i++)
	{
		if (SGET(i, sh_type) == SHT_SYMTAB)
		{
			printf("a\n");
		}
	}
}