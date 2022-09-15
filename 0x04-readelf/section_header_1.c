#include "lib_elf.h"

int main(int argc, char **argv)
{
	Elf64_Shdr *shdr = NULL;
        Elf64_Ehdr *ehdr = NULL;
        int fd = 0, rd = 0, size = 0, len = 0;

        if (argc != 2)
        {
                fprintf(stderr, "Usage: 0-hreadelf elf_filename\n");
                exit(98);
        }
        fd = process_ehdr(&ehdr, argv[1]);
        len = ehdr->e_shnum;
        section_header_1(ehdr);
        size = sizeof(Elf64_Shdr) * len * len;
        shdr = malloc(size);
        if (shdr == NULL)
        {
                fprintf(stderr, "Can't malloc\n");
                exit(98);
        }
        rd = read(fd, shdr, size);
        if (rd == -1)
        {
                fprintf(stderr, "Can't read file %s\n", argv[1]);
                exit(98);
        }
        
	section_header_2(shdr, ehdr, len, fd);

	return (0);
}

void section_header_1(Elf64_Ehdr *header)
{
        char *str = NULL;

        check_elf(header);

        str = section_headers_number(header);
        printf("There are %s program headers", str);

        str = start_program_headers(header);
        printf(", starting at offset %s\n\n", str);
}

void section_header_2(Elf64_Shdr *shdr, Elf64_Ehdr *ehdr, int len, int fd)
{
        int i = 0;
        
        char *str = NULL, *str2= NULL;
        Elf64_Shdr *tmp = NULL;

	printf("  [Nr] Name              Type            ");
	printf("Address          Off    Size   ES Flg Lk Inf Al\n");

        
        str = malloc(sizeof(ehdr->e_shnum) * ehdr->e_shentsize * ehdr->e_shnum);
        if (!str)
                exit(1);
        lseek(fd, ehdr->e_shoff, SEEK_SET);
        read(fd, str,  ehdr->e_shnum * ehdr->e_shnum);
        shdr = (Elf64_Shdr *)str;
        tmp = &shdr[ehdr->e_shstrndx] + ehdr->e_shoff;
        str2 = str + tmp->sh_offset;
        for (i = 0; i < len; i++)
        {
                printf("size %d offset %ld | fd %d\n", shdr[i].sh_name, ehdr->e_shoff, fd);
                printf("  [%02d] ", i);
                printf("name => %s\n", str2 + shdr[i].sh_name);
        }
}


char *section_header_name(Elf64_Shdr shdr)
{
        if (shdr.sh_type == SHT_PROGBITS)
                return ("PROGBITS");
        if (shdr.sh_type == SHT_SYMTAB)
                return ("SYMTAB");
        if (shdr.sh_type == SHT_STRTAB)
                return ("STRTAB");
        if (shdr.sh_type == SHT_RELA)
                return ("RELA");
        if (shdr.sh_type == SHT_HASH)
                return ("HASH");
        if (shdr.sh_type == SHT_DYNAMIC)
                return ("DYNAMIC");
        if (shdr.sh_type == SHT_NOTE)
                return ("NOTE");
        if (shdr.sh_type == SHT_NOBITS)
                return ("NOBITS");
        if (shdr.sh_type == SHT_REL)
                return ("REL");
        if (shdr.sh_type == SHT_SHLIB)
                return ("SHLIB");
        if (shdr.sh_type == SHT_DYNSYM)
                return ("DYNSYM");
        if (shdr.sh_type == SHT_LOPROC)
                return ("LOPROC");
        if (shdr.sh_type == SHT_HIPROC)
                return ("HIPROC");
        if (shdr.sh_type == SHT_LOUSER)
                return ("LOUSER");
        if (shdr.sh_type == SHT_HIUSER)
                return ("HIUSER");
        else /* (shdr.sh_type == SHT_NULL) */
                return ("NULL");
}
