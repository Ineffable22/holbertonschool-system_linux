#include "lib_elf.h"

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

/**
 * os_abi - Identifies the operating system
 * @header: Pointer to the ELF header
 *
 * Return: Nothing
 */
char *os_abi(Elf64_Ehdr *header)
{
	if (header->e_ident[EI_OSABI] == ELFOSABI_HPUX)
		return ("HP-UX");
	if (header->e_ident[EI_OSABI] == ELFOSABI_NETBSD)
		return ("NetBSD");
	if (header->e_ident[EI_OSABI] == ELFOSABI_LINUX)
		return ("Linux");
	if (header->e_ident[EI_OSABI] == ELFOSABI_SOLARIS)
		return ("Solaris");
	if (header->e_ident[EI_OSABI] == ELFOSABI_IRIX)
		return ("IRIX");
	if (header->e_ident[EI_OSABI] == ELFOSABI_FREEBSD)
		return ("FreeBSD");
	if (header->e_ident[EI_OSABI] == ELFOSABI_TRU64)
		return ("TRU64 UNIX");
	if (header->e_ident[EI_OSABI] == ELFOSABI_ARM)
		return ("ARM architecture");
	if (header->e_ident[EI_OSABI] == ELFOSABI_STANDALONE)
		return ("Stand-alone (embedded)");

	/* EI_OSABI == ELFOSABI_NONE || ELFOSABI_SYSV */
	return ("UNIX - System V");
}
