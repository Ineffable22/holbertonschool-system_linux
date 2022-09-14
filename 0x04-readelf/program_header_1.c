#include "lib_elf.h"

void first2(Elf64_Phdr *shdr, int fd);
int main(int argc, char **argv)
{
	Elf64_Phdr *phdr, size;
        int fd = 0, rd = 0;

        if (argc != 2)
        {
                fprintf(stderr, "Usage: 0-hreadelf elf_filename\n");
                exit(98);
        }

        phdr = malloc(sizeof(size));
        if (phdr == NULL)
        {
                fprintf(stderr, "Can't malloc\n");
                exit(98);
        }
        fd = open(argv[1], O_RDONLY);
        if (fd == -1)
        {
                fprintf(stderr, "Can't open file %s\n", argv[1]);
                exit(98);
        }
        rd = read(fd, phdr, sizeof(size));
        if (rd == -1)
        {
                fprintf(stderr, "Can't read file %s\n", argv[1]);
                exit(98);
        }
	first2(phdr, fd);
	return (0);
}

void first2(Elf64_Phdr *phdr, int fd)
{
	(void) fd;
	printf("Data => %x\n", phdr->p_type);
}
