#include "lib_elf.h"

/**
 * main - Displays the information contained in the ELF file header
 * of an ELF file.
 * @argc: Arguments number
 * @argv: Each argument per pointer
 *
 * Return: 0 if successful, else exit on error
 */
int main(int argc, char **argv)
{
	Elf64_Ehdr *header = NULL, size;
	int fd = 0, rd = 0;

	if (argc != 2)
	{
		fprintf(stderr, "Usage: 0-hreadelf elf_filename\n");
		exit(98);
	}

	header = malloc(sizeof(size));
	if (header == NULL)
	{
		fprintf(stderr, "Can't malloc\n");
		exit(98);
	}
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
	{
		fprintf(stderr, "Can't open file %s\n", argv[1]);
		exit(98);
	}
	rd = read(fd, header, sizeof(size));
	if (rd == -1)
	{
		fprintf(stderr, "Can't read file %s\n", argv[1]);
		exit(98);
	}
	check_elf(header);
	osabi(header);
	machine(header);
	version(header);
	number(header);
	free(header);
	return (0);
}


/**
 * check_elf - Checks if file is ELF file
 * @header: Pointer to the ELF header
 *
 * Return: Nothing
 */
void check_elf(Elf64_Ehdr *header)
{
	int i = 0;

	if (header->e_ident[EI_MAG0] != 0x7f ||
	    header->e_ident[EI_MAG1] != 'E' ||
	    header->e_ident[EI_MAG2] != 'L' ||
	    header->e_ident[EI_MAG3] != 'F')
	{
		printf("readelf: Error: Not an ELF file - it has the wrong");
		printf("magic bytes at the start\n");
		exit(1);
	}
	printf("ELF Header:\n");
	printf("  Magic:   ");
	for (i = 0; i != EI_NIDENT; i++)
	{
		printf("%02x ", header->e_ident[i]);
	}
	putchar(0xa);
	if (header->e_ident[EI_CLASS] == ELFCLASS32)
		printf("  Class:                             ELF32\n");
	if (header->e_ident[EI_CLASS] == ELFCLASS64)
		printf("  Class:                             ELF64\n");
	if (header->e_ident[EI_DATA] == ELFDATA2LSB)
	{
		printf("  Data:                              2's complement,");
		printf("little-endian\n");
	}
	if (header->e_ident[EI_DATA] == ELFDATA2MSB)
		printf("  Data:                              2's complement, big-endian\n");

	if (header->e_ident[EI_VERSION] == EV_NONE)
		printf("  Version:                           Invalid version\n");
	if (header->e_ident[EI_VERSION] == EV_CURRENT)
		printf("  Version:                           1 (current)\n");
}

/**
 * osabi - Identifies the operating system
 * @header: Pointer to the ELF header
 *
 * Return: Nothing
 */
void osabi(Elf64_Ehdr *header)
{
	if (header->e_ident[EI_OSABI] == ELFOSABI_NONE)
		printf("  OS/ABI:                            UNIX System V\n");
	if (header->e_ident[EI_OSABI] == ELFOSABI_HPUX)
		printf("  OS/ABI:                            HP-UX\n");
	if (header->e_ident[EI_OSABI] == ELFOSABI_NETBSD)
		printf("  OS/ABI:                            NetBSD\n");
	if (header->e_ident[EI_OSABI] == ELFOSABI_LINUX)
		printf("  OS/ABI:                            Linux\n");
	if (header->e_ident[EI_OSABI] == ELFOSABI_SOLARIS)
		printf("  OS/ABI:                            Solaris\n");
	if (header->e_ident[EI_OSABI] == ELFOSABI_IRIX)
		printf("  OS/ABI:                            IRIX\n");
	if (header->e_ident[EI_OSABI] == ELFOSABI_FREEBSD)
		printf("  OS/ABI:                            FreeBSD\n");
	if (header->e_ident[EI_OSABI] == ELFOSABI_TRU64)
		printf("  OS/ABI:                            TRU64 UNIX\n");
	if (header->e_ident[EI_OSABI] == ELFOSABI_ARM)
		printf("  OS/ABI:                            ARM architecture\n");
	if (header->e_ident[EI_OSABI] == ELFOSABI_STANDALONE)
		printf("  OS/ABI:                            Stand-alone (embedded)\n");
	if (header->e_ident[EI_ABIVERSION] == 0)
		printf("  ABI Version:                       0\n");
	if (header->e_ident[EI_ABIVERSION] == 1)
		printf("  ABI Version:                       1\n");

	if (header->e_type == ET_NONE)
		printf("  Type:                              NONE (An unknown type)\n");
	if (header->e_type == ET_REL)
		printf("  Type:                              REL (A relocatable file)\n");
	if (header->e_type == ET_EXEC)
		printf("  Type:                              EXEC (An executable file)\n");
	if (header->e_type == ET_DYN)
		printf("  Type:                              DYN (A shared object)\n");
	if (header->e_type == ET_CORE)
		printf("  Type:                              CORE (A core file)\n");
}

/**
 * machine - Identifies the type of machine
 * @header: Pointer to the ELF header
 *
 * Return: Nothing
 */
void machine(Elf64_Ehdr *header)
{
	printf("  Machine:                           ");
	if (header->e_machine == EM_NONE)
		printf("An unknown machine\n");
	if (header->e_machine == EM_M32)
		printf("AT&T WE 32100\n");
	if (header->e_machine == EM_SPARC)
		printf("Sun Microsystems SPARC\n");
	if (header->e_machine == EM_386)
		printf("Intel 80386\n");
	if (header->e_machine == EM_68K)
		printf("Motorola 68000\n");
	if (header->e_machine == EM_88K)
		printf("Motorola 88000\n");
	if (header->e_machine == EM_860)
		printf("Intel 80860\n");
	if (header->e_machine == EM_MIPS)
		printf("MIPS RS3000 (big-endian only)\n");
	if (header->e_machine == EM_PARISC)
		printf("HP/PA\n");
	if (header->e_machine == EM_SPARC32PLUS)
		printf("SPARC with enhanced instruction set\n");
	if (header->e_machine == EM_PPC)
		printf("PowerPC\n");
	if (header->e_machine == EM_PPC64)
		printf("PowerPC 64-bit\n");
	if (header->e_machine == EM_S390)
		printf("IBM S/390\n");
	if (header->e_machine == EM_ARM)
		printf("Advanced RISC Machines\n");
	if (header->e_machine == EM_SH)
		printf("Renesas SuperH\n");
	if (header->e_machine == EM_SPARCV9)
		printf("SPARC v9 64-bit\n");
	if (header->e_machine == EM_IA_64)
		printf("Intel Itanium\n");
	if (header->e_machine == EM_X86_64)
		printf("Advanced Micro Devices x86-64\n");
	if (header->e_machine == EM_VAX)
		printf("DEC Vax\n");
}
