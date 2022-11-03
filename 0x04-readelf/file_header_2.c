#include "lib_elf.h"

/**
 * os_abi - Identifies the operating system
 * @eh: Pointer to the ELF eh
 *
 * Return: Nothing
 */
char *os_abi(elf eh)
{
	if (EGET(e_ident[EI_OSABI]) == ELFOSABI_HPUX)
		return ("HP-UX");
	if (EGET(e_ident[EI_OSABI]) == ELFOSABI_NETBSD)
		return ("NetBSD");
	if (EGET(e_ident[EI_OSABI]) == ELFOSABI_LINUX)
		return ("Linux");
	if (EGET(e_ident[EI_OSABI]) == ELFOSABI_SOLARIS)
		return ("Solaris");
	if (EGET(e_ident[EI_OSABI]) == ELFOSABI_IRIX)
		return ("IRIX");
	if (EGET(e_ident[EI_OSABI]) == ELFOSABI_FREEBSD)
		return ("FreeBSD");
	if (EGET(e_ident[EI_OSABI]) == ELFOSABI_TRU64)
		return ("TRU64 UNIX");
	if (EGET(e_ident[EI_OSABI]) == ELFOSABI_ARM)
		return ("ARM architecture");
	if (EGET(e_ident[EI_OSABI]) == ELFOSABI_STANDALONE)
		return ("Stand-alone (embedded)");

	/* EI_OSABI == ELFOSABI_NONE || ELFOSABI_SYSV */
	return ("UNIX - System V");
}

/**
 * abi_version - Checks the ABI version of the file
 * @eh: Pointer to the ELF eh
 *
 * Return: Resulting string
 */
char *abi_version(elf eh)
{
	if (EGET(e_ident[EI_ABIVERSION]) == 1)
		return ("1");
	else /* (EGET(e_ident[EI_ABIVERSION] == 0) */
		return ("0");
}

/**
 * type - Checks the file type
 * @eh: Pointer to the ELF eh
 *
 * Return: Resulting string
 */
char *type(elf eh)
{
	if (EGET(e_type) == ET_REL)
		return ("REL (A relocatable file)");
	if (EGET(e_type) == ET_EXEC)
		return ("EXEC (An executable file)");
	if (EGET(e_type) == ET_DYN)
		return ("DYN (Shared object file)");
	if (EGET(e_type) == ET_CORE)
		return ("CORE (A core file)");
	else /* (EGET(e_type == ET_NONE) */
		return ("NONE (An unknown type)");
}

/**
 * machine - Identifies the type of machine
 * @eh: Pointer to the ELF eh
 *
 * Return: Nothing
 */
char *machine(elf eh)
{
	if (EGET(e_machine) == EM_M32)
		return ("AT&T WE 32100");
	if (EGET(e_machine) == EM_SPARC)
		return ("Sun Microsystems SPARC");
	if (EGET(e_machine) == EM_386)
		return ("Intel 80386");
	if (EGET(e_machine) == EM_68K)
		return ("Motorola 68000");
	if (EGET(e_machine) == EM_88K)
		return ("Motorola 88000");
	if (EGET(e_machine) == EM_860)
		return ("Intel 80860");
	if (EGET(e_machine) == EM_MIPS)
		return ("MIPS RS3000 (big-endian only)");
	if (EGET(e_machine) == EM_PARISC)
		return ("HP/PA");
	if (EGET(e_machine) == EM_SPARC32PLUS)
		return ("SPARC with enhanced instruction set");
	if (EGET(e_machine) == EM_PPC)
		return ("PowerPC");
	if (EGET(e_machine) == EM_PPC64)
		return ("PowerPC 64-bit");
	if (EGET(e_machine) == EM_S390)
		return ("IBM S/390");
	if (EGET(e_machine) == EM_ARM)
		return ("Advanced RISC Machines");
	if (EGET(e_machine) == EM_SH)
		return ("Renesas SuperH");
	if (EGET(e_machine) == EM_SPARCV9)
		return ("SPARC v9 64-bit");
	if (EGET(e_machine) == EM_IA_64)
		return ("Intel Itanium");
	if (EGET(e_machine) == EM_X86_64)
		return ("Advanced Micro Devices x86-64");
	if (EGET(e_machine) == EM_VAX)
		return ("DEC Vax");
	else /* (EGET(e_machine == EM_NONE) */
		return ("An unknown machine");
}

/**
 * version_1 - Identifies the version and address
 * @eh: Pointer to the ELF eh
 *
 * Return: Nothing
 */
char *version_1(elf eh)
{
	if (EGET(e_version) == EV_CURRENT)
		return ("1");
	else /* (EGET(e_version) == EV_NONE) */
		return ("0");
}
