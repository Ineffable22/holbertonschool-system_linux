#include "lib_elf.h"

void first(Elf64_Shdr *shdr, int fd);
int main(int argc, char **argv)
{
	Elf64_Shdr *shdr, size;
        int fd = 0, rd = 0;

        if (argc != 2)
        {
                fprintf(stderr, "Usage: 0-hreadelf elf_filename\n");
                exit(98);
        }

        shdr = malloc(sizeof(size));
        if (shdr == NULL)
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
        rd = read(fd, shdr, sizeof(size));
        if (rd == -1)
        {
                fprintf(stderr, "Can't read file %s\n", argv[1]);
                exit(98);
        }
	first(shdr, fd);
	return (0);
}

void first(Elf64_Shdr *shdr, int fd)
{
	lseek()
	printf("  [Nr] Name              Type            ");
	printf("Address          Off    Size   ES Flg Lk Inf Al\n");
	printf("Number => %lx\n", shdr->sh_offset);
	printf("Number => %x\n", shdr->sh_name);
	printf("Number => %ld\n", shdr->sh_addr);
	printf("Number => %ld\n", shdr->sh_offset);

}
