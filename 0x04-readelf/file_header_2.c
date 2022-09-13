#include "lib_elf.h"

/**
 * version - Identifies the version and address
 * @header: Pointer to the ELF header
 *
 * Return: Nothing
 */
void version(Elf64_Ehdr *header)
{
	printf("  Version:                           ");
	if (header->e_version == EV_NONE)
		printf("0x0\n");
	if (header->e_version == EV_CURRENT)
		printf("0x1\n");

	if (header->e_entry)
		printf("  Entry Point Address:               0x%lx\n", header->e_entry);
	else
		printf("  Entry Point Address:               0x0\n");

	printf("  Start of program headers:          ");
	if (header->e_phoff)
		printf("%ld (bytes into file)\n", header->e_phoff);
	else
		printf("0\n");

	printf("  Start of section headers:          ");
	if (header->e_shoff)
		printf("%ld (bytes into file)\n", header->e_shoff);
	else
		printf("0\n");

	printf("  Flags:                             ");
	if (header->e_flags)
		printf("0x%x (bytes into file)\n", header->e_flags);
	else
		printf("0x0\n");

	printf("  Size of this header:               ");
	if (header->e_ehsize)
		printf("%d (bytes)\n", header->e_ehsize);
	else
		printf("0\n");

	printf("  Size of program headers:           ");
	if (header->e_phentsize)
		printf("%d (bytes)\n", header->e_phentsize);
	else
		printf("0\n");
}

/**
 * number - Identifies the number or size of headers
 * @header: Pointer to the ELF header
 *
 * Return: Nothing
 */
void number(Elf64_Ehdr *header)
{
	printf("  Number of program headers:         ");
	if (header->e_phnum < PN_XNUM)
		printf("%d\n", header->e_phnum);
	else
		printf("0\n");

	printf("  Size of section headers:           ");
	if (header->e_shentsize)
		printf("%d (bytes)\n", header->e_shentsize);
	else
		printf("0 (bytes)\n");

	printf("  Number of section headers:         ");
	if (header->e_shnum)
		printf("%d\n", header->e_shnum);
	else
		printf("0\n");

	printf("  Section header string table index: ");
	if (header->e_shstrndx)
		printf("%d\n", header->e_shstrndx);
	else
		printf("0\n");
}
