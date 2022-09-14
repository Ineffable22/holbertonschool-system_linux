#include "lib_elf.h"

/**
 * check_elf - Checks if file is ELF file
 * @header: Pointer to the ELF header
 *
 * Return: Nothing
 */
void check_elf(Elf64_Ehdr *header)
{
	if (header->e_ident[EI_MAG0] != 0x7f ||
	    header->e_ident[EI_MAG1] != 'E' ||
	    header->e_ident[EI_MAG2] != 'L' ||
	    header->e_ident[EI_MAG3] != 'F')
	{
		printf("readelf: Error: Not an ELF file - it has the wrong");
		printf("magic bytes at the start\n");
		exit(1);
	}
}

/**
 * magic_number - Prints the magic number
 * @header: Pointer to the ELF header
 *
 * Return: Nothing
 */
void magic_number(Elf64_Ehdr *header)
{
	int i = 0;

	printf("ELF Header:\n");
	printf("  Magic:   ");
	for (i = 0; i != EI_NIDENT; i++)
		printf("%02x ", header->e_ident[i]);
	putchar(0xa);
}

/**
 * class_file - Checks the class of the file
 * @header: Pointer to the ELF header
 *
 * Return: Resulting string
 */
char *class_file(Elf64_Ehdr *header)
{
	if (header->e_ident[EI_CLASS] == ELFCLASS32)
		return ("ELF32");
	else if (header->e_ident[EI_CLASS] == ELFCLASS64)
		return ("ELF64");
	else /* ELFCLASSNONE */
		return ("invalid");
}

/**
 * data - Checks the data of the file
 * @header: Pointer to the ELF header
 *
 * Return: Resulting string
 */
char *data(Elf64_Ehdr *header)
{
	if (header->e_ident[EI_DATA] == ELFDATA2LSB)
		return ("2's complement, little endian");

	else if (header->e_ident[EI_DATA] == ELFDATA2MSB)
		return ("2's complement, big endian");
	else /* ELFDATANONE */
		return ("Unknown data format");
}

/**
 * version_0 - Checks the version of the file
 * @header: Pointer to the ELF header
 *
 * Return: Resulting string
 */
char *version_0(Elf64_Ehdr *header)
{
	if (header->e_ident[EI_VERSION] == EV_CURRENT)
		return ("1 (current)");
	else /* (header->e_ident[EI_VERSION] == EV_NONE) */
		return ("Invalid version");
}
