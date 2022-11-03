#include "lib_elf.h"

/**
 * point_address - Identifies the entry point address
 * @eh: Pointer to the ELF eh
 *
 * Return: Resulting string
 */
char *point_address(elf eh)
{
	if (EGET(e_entry))
	{
		return (itoa(EGET(e_entry), 16));
	}
	else
		return ("0");
}

/**
 * start_program_headers - Identifies the start of program headers
 * @eh: Pointer to the ELF eh
 *
 * Return: Resulting string
 */
char *start_program_headers(elf eh)
{
	if (EGET(e_phoff))
		return (itoa(EGET(e_phoff), 10));
	else
		return ("0");
}

/**
 * start_section_headers - Identifies the start of section headers
 * @eh: Pointer to the ELF eh
 *
 * Return: Resulting string
 */
char *start_section_headers(elf eh)
{
	if (EGET(e_shoff))
		return (itoa(EGET(e_shoff), 10));
	else
		return ("0");
}

/**
 * flags - Identifies the flags
 * @eh: Pointer to the ELF eh
 *
 * Return: Resulting string
 */
char *flags(elf eh)
{
	if (EGET(e_flags))
		return (itoa(EGET(e_flags), 16));
	else
		return ("0");
}

/**
 * header_size - Identifies the size of this eh
 * @eh: Pointer to the ELF eh
 *
 * Return: Resulting string
 */
char *header_size(elf eh)
{
	if (EGET(e_ehsize))
		return (itoa(EGET(e_ehsize), 10));
	else
		return ("0");
}
