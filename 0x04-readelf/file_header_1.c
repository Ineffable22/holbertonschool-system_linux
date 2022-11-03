#include "lib_elf.h"

/**
 * check_elf - Checks if file is ELF file
 * @eh: Pointer to the ELF eh
 *
 * Return: Nothing
 */
void check_elf(elf eh)
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

/**
 * magic_number - Prints the magic number
 * @eh: Pointer to the ELF eh
 *
 * Return: Nothing
 */
void magic_number(elf eh)
{
	int i = 0;

	printf("ELF Header:\n");
	printf("  Magic:   ");
	for (i = 0; i != EI_NIDENT; i++)
		printf("%02x ", EGET(e_ident[i]));
	putchar(0xa);
}

/**
 * class_file - Checks the class of the file
 * @eh: Pointer to the ELF eh
 *
 * Return: Resulting string
 */
char *class_file(elf eh)
{
	if (eh.eh32.e_ident[EI_CLASS] == ELFCLASS32)
		return ("ELF32");
	else if (CHECK_64(eh.eh64))
		return ("ELF64");
	else /* ELFCLASSNONE */
		return ("invalid");
}

/**
 * data - Checks the data of the file
 * @eh: Pointer to the ELF eh
 *
 * Return: Resulting string
 */
char *data(elf eh)
{
	if (EGET(e_ident[EI_DATA]) == ELFDATA2LSB)
		return ("2's complement, little endian");

	else if (EGET(e_ident[EI_DATA]) == ELFDATA2MSB)
		return ("2's complement, big endian");
	else /* ELFDATANONE */
		return ("Unknown data format");
}

/**
 * version_0 - Checks the version of the file
 * @eh: Pointer to the ELF eh
 *
 * Return: Resulting string
 */
char *version_0(elf eh)
{
	if (EGET(e_ident[EI_VERSION]) == EV_CURRENT)
		return ("1 (current)");
	else /* (eh->e_ident[EI_VERSION] == EV_NONE) */
		return ("Invalid version");
}
