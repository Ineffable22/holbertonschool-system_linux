#include "lib_elf.h"

/**
 * switch_endian2 - switches endianness on 2 byte unsigned int
 * @n: the unsigned int whose bytes to switch
 * Return: unsigned int with switched bytes
 */
unsigned short switch_endian2(unsigned short n)
{
	return (((n >> 8) & 0x00ff) |
		((n << 8) & 0xff00));
}

/**
 * switch_endian4 - switches endianness on 4 byte unsigned int
 * @n: the unsigned int whose bytes to switch
 * Return: unsigned int with switched bytes
 */
unsigned int switch_endian4(unsigned int n)
{
	return (((n >> 24) & 0x000000ff) |
		((n >> 8) & 0x0000ff00) |
		((n << 8) & 0x00ff0000) |
		((n << 24) & 0xff000000));
}

/**
 * switch_endian8 - switches endianness on 8 byte unsigned int
 * @n: the unsigned int whose bytes to switch
 * Return: unsigned int with switched bytes
 */
unsigned long switch_endian8(unsigned long n)
{
	return (((n >> 56) & 0x00000000000000ff) |
		((n >> 40) & 0x000000000000ff00) |
		((n >> 24) & 0x0000000000ff0000) |
		((n >> 8) & 0x00000000ff000000) |
		((n << 8) & 0x000000ff00000000) |
		((n << 24) & 0x0000ff0000000000) |
		((n << 40) & 0x00ff000000000000) |
		((n << 56) & 0xff00000000000000));
}

/**
* switch_endians - Check and switch endians
* @eh: Pointer to the ELF eh
*
* return: Nothing
*/
void switch_endians(elf *eh)
{
	if (eh->eh64.e_ident[EI_DATA] == ELFDATA2MSB)
	{
		eh->eh64.e_type = switch_endian2(eh->eh64.e_type);
		eh->eh64.e_machine = switch_endian2(eh->eh64.e_machine);
		eh->eh64.e_version = switch_endian4(eh->eh64.e_version);
		eh->eh64.e_entry = switch_endian8(eh->eh64.e_entry);
		eh->eh64.e_phoff = switch_endian8(eh->eh64.e_phoff);
		eh->eh64.e_shoff = switch_endian8(eh->eh64.e_shoff);
		eh->eh64.e_flags = switch_endian4(eh->eh64.e_flags);
		eh->eh64.e_ehsize = switch_endian2(eh->eh64.e_ehsize);
		eh->eh64.e_phentsize = switch_endian2(eh->eh64.e_phentsize);
		eh->eh64.e_phnum = switch_endian2(eh->eh64.e_phnum);
		eh->eh64.e_shentsize = switch_endian2(eh->eh64.e_shentsize);
		eh->eh64.e_shnum = switch_endian2(eh->eh64.e_shnum);
		eh->eh64.e_shstrndx = switch_endian2(eh->eh64.e_shstrndx);
	}
	if (eh->eh64.e_ident[EI_DATA] == ELFDATA2MSB &&
	 eh->eh64.e_ident[EI_CLASS] == ELFCLASS32)
	{
		eh->eh32.e_type = switch_endian2(eh->eh32.e_type);
		eh->eh32.e_machine = switch_endian2(eh->eh32.e_machine);
		eh->eh32.e_version = switch_endian4(eh->eh32.e_version);
		eh->eh32.e_entry = switch_endian4(eh->eh32.e_entry);
		eh->eh32.e_phoff = switch_endian4(eh->eh32.e_phoff);
		eh->eh32.e_shoff = switch_endian4(eh->eh32.e_shoff);
		eh->eh32.e_flags = switch_endian4(eh->eh32.e_flags);
		eh->eh32.e_ehsize = switch_endian2(eh->eh32.e_ehsize);
		eh->eh32.e_phentsize = switch_endian2(eh->eh32.e_phentsize);
		eh->eh32.e_phnum = switch_endian2(eh->eh32.e_phnum);
		eh->eh32.e_shentsize = switch_endian2(eh->eh32.e_shentsize);
		eh->eh32.e_shnum = switch_endian2(eh->eh32.e_shnum);
		eh->eh32.e_shstrndx = switch_endian2(eh->eh32.e_shstrndx);
	}
}
