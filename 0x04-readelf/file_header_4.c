#include "lib_elf.h"

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

/**
 * program_headers_number - Identifies the number of program headers
 * @header: Pointer to the ELF header
 *
 * Return: Resulting string
 */
char *program_headers_number(Elf64_Ehdr *header)
{
	if (header->e_phnum < PN_XNUM)
		return (itoa(header->e_phnum, 10));
	else
		return ("0");
}

/**
 * section_headers_size - Identifies the size of section headers
 * @header: Pointer to the ELF header
 *
 * Return: Resulting string
 */
char *section_headers_size(Elf64_Ehdr *header)
{
	if (header->e_shentsize)
		return (itoa(header->e_shentsize, 10));
	else
		return ("0");
}

/**
 * section_headers_number - Identifies the number of section headers
 * @header: Pointer to the ELF header
 *
 * Return: Resulting string
 */
char *section_headers_number(Elf64_Ehdr *header)
{
	if (header->e_shnum)
		return (itoa(header->e_shnum, 10));
	else
		return ("0");
}

/**
 * section_headers_index - Identifies the section header string table index
 * @header: Pointer to the ELF header
 *
 * Return: Resulting string
 */
char *section_headers_index(Elf64_Ehdr *header)
{
	if (header->e_shstrndx)
		return (itoa(header->e_shstrndx, 10));
	else
		return ("0\n");
}
