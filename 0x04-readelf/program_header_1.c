#include "lib_elf.h"

/**
 * main - Displays the information contained in the ELF program header
 * of an ELF file.
 * @argc: Arguments number
 * @argv: Each argument per pointer
 *
 * Return: 0 if successful, else exit on error
 */
int main(int argc, char **argv)
{
	Elf64_Phdr *phdr = NULL;
	Elf64_Ehdr *ehdr = NULL;
	Elf64_Shdr *shdr = NULL;
	int fd = 0, rd = 0, len = 0, size = 0;

	if (argc != 2)
	{
		fprintf(stderr, "Usage: 0-hreadelf elf_filename\n");
		exit(98);
	}
	fd = process_ehdr(&ehdr, argv[1]);
	len = program_header_1(ehdr);
	size = sizeof(Elf64_Phdr) * len;
	phdr = malloc(size);
	if (phdr == NULL)
	{
		fprintf(stderr, "Can't malloc\n");
		exit(98);
	}
	rd = read(fd, phdr, size);
	if (rd == -1)
	{
		fprintf(stderr, "Can't read file %s\n", argv[1]);
		exit(98);
	}
	program_header_2(phdr, len);
	size = sizeof(Elf64_Shdr) * len;
	shdr = malloc(size);
	if (phdr == NULL)
	{
		fprintf(stderr, "Can't malloc\n");
		exit(98);
	}
	rd = read(fd, shdr, size);
	if (rd == -1)
	{
		fprintf(stderr, "Can't read file %s\n", argv[1]);
		exit(98);
	} /*program_header_3(shdr, len, fd, ehdr);*/
	return (0);
}

/**
 * program_header_1 - Checks if file is ELF file
 * @header: Pointer to the ELF header
 *
 * Return: length
 */
int program_header_1(Elf64_Ehdr *header)
{
	char *str = NULL;

	check_elf(header);

	str = type(header);
	printf("Elf file type is %s\n", str);

	str = point_address(header);
	printf("Entry point 0x%s\n", str);

	str = program_headers_number(header);
	printf("There are %s program headers", str);

	str = start_program_headers(header);
	printf(", starting at offset %s\n\n", str);
	printf("Program Headers:\n");

	return (header->e_phnum);
}

/**
 * program_header_2 - Prints first section
 * @phdr: Pointer to the ELF header
 * @len: Length of header
 *
 * Return: Nothing
 */
void program_header_2(Elf64_Phdr *phdr, int len)
{
	int i = 0;

	printf("  Type           Offset   VirtAddr           PhysAddr");
	printf("           FileSiz  MemSiz   Flg Align\n");
	for (i = 0; i < len; i++)
	{
		printer_program_header(phdr[i]);
	}
	printf("\nSection to Segment mapping:\n");
	printf("Segment Sections...\n");

}

/**
 * printer_program_header - Prints second section
 * @phdr: Pointer to the ELF header
 *
 * Return: Nothing
 */
void printer_program_header(Elf64_Phdr phdr)
{
	int i = 0, len = 0;
	char *type = NULL;

	type = ptype(phdr.p_type);
	printf("  %s", type);
	for (i = 0; i < 15 - _strlen(type); i++)
		putchar(0x20);

	printf("0x%06lx ", phdr.p_offset);
	printf("0x%016lx ", phdr.p_vaddr);
	printf("0x%016lx ", phdr.p_paddr);
	printf("0x%06lx ", phdr.p_filesz);
	printf("0x%06lx ", phdr.p_memsz);

	if (phdr.p_flags & PF_R)
		len++, printf("R");
	if (phdr.p_flags & PF_W)
		len++, printf("W");
	if (phdr.p_flags & PF_X)
		len += 2, printf(" E");
	for (i = 4; i > len; i--)
		putchar(0x20);
	printf("0x%lx ", phdr.p_align);
	putchar(0xa);
}

/**
 * ptype - Identifies the type of program header
 * @type: Integer with data type
 *
 * Return: Resulting string
 */
char *ptype(int type)
{
	if (type == PT_LOAD)
		return ("LOAD");
	if (type == PT_DYNAMIC)
		return ("DYNAMIC");
	if (type == PT_INTERP)
		return ("INTERP");
	if (type == PT_NOTE)
		return ("NOTE");
	if (type == PT_SHLIB)
		return ("SHLIB");
	if (type == PT_PHDR)
		return ("PHDR");
	if (type == PT_HIPROC)
		return ("HIPROC");
	if (type == PT_LOPROC)
		return ("LOPROC");
	if (type == PT_GNU_STACK)
		return ("GNU_STACK");
	else /* (type == PT_NULL) */
		return ("NULL");
}
