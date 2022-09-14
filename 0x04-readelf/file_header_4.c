#include "lib_elf.h"

/**
 * start_program_headers - Identifies the start of program headers
 * @header: Pointer to the ELF header
 *
 * Return: Resulting string
 */
char *start_program_headers(Elf64_Ehdr *header)
{
	if (header->e_phoff)
		return (itoa(header->e_phoff, 10));
	else
		return ("0");
}

/**
 * start_section_headers - Identifies the start of section headers
 * @header: Pointer to the ELF header
 *
 * Return: Resulting string
 */
char *start_section_headers(Elf64_Ehdr *header)
{
	if (header->e_shoff)
		return (itoa(header->e_shoff, 10));
	else
		return ("0");
}

/**
 * flags - Identifies the flags
 * @header: Pointer to the ELF header
 *
 * Return: Resulting string
 */
char *flags(Elf64_Ehdr *header)
{
	if (header->e_flags)
		return (itoa(header->e_flags, 16));
	else
		return ("0");
}

/**
 * header_size - Identifies the size of this header
 * @header: Pointer to the ELF header
 *
 * Return: Resulting string
 */
char *header_size(Elf64_Ehdr *header)
{
	if (header->e_ehsize)
		return (itoa(header->e_ehsize, 10));
	else
		return ("0");
}

/**
 * program_header_size - Identifies the size of program headers
 * @header: Pointer to the ELF header
 *
 * Return: Resulting string
 */
char *program_header_size(Elf64_Ehdr *header)
{
	if (header->e_phentsize)
		return (itoa(header->e_phentsize, 10));
	else
		return ("0");
}
