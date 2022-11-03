#include "lib_elf.h"

/**
 * program_header_size - Identifies the size of program headers
 * @eh: Pointer to the ELF eh
 *
 * Return: Resulting string
 */
char *program_header_size(elf eh)
{
	if (EGET(e_phentsize))
		return (itoa(EGET(e_phentsize), 10));
	else
		return ("0");
}

/**
 * program_headers_number - Identifies the number of program headers
 * @eh: Pointer to the ELF eh
 *
 * Return: Resulting string
 */
char *program_headers_number(elf eh)
{
	if (EGET(e_phnum < PN_XNUM))
		return (itoa(EGET(e_phnum), 10));
	else
		return ("0");
}

/**
 * section_headers_size - Identifies the size of section headers
 * @eh: Pointer to the ELF eh
 *
 * Return: Resulting string
 */
char *section_headers_size(elf eh)
{
	if (EGET(e_shentsize))
		return (itoa(EGET(e_shentsize), 10));
	else
		return ("0");
}

/**
 * section_headers_number - Identifies the number of section headers
 * @eh: Pointer to the ELF eh
 *
 * Return: Resulting string
 */
char *section_headers_number(elf eh)
{
	if (EGET(e_shnum))
		return (itoa(EGET(e_shnum), 10));
	else
		return ("0");
}

/**
 * section_headers_index - Identifies the section eh string table index
 * @eh: Pointer to the ELF eh
 *
 * Return: Resulting string
 */
char *section_headers_index(elf eh)
{
	if (EGET(e_shstrndx))
		return (itoa(EGET(e_shstrndx), 10));
	else
		return ("0\n");
}
