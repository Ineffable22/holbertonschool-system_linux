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
	elf eh;
	int fd = 0, rd = 0;

	if (argc != 2)
	{
		fprintf(stderr, "Usage: 0-hreadelf elf_filename\n");
		exit(98);
	}
	memset(&eh, 0, sizeof(eh));
	fd = process_ehdr(&eh, argv[1]);
	if (!CHECK_64(eh.eh64))
	{
		lseek(fd, 0, SEEK_SET);
		rd = read(fd, &eh.eh32, sizeof(eh.eh32));
		if (rd == -1 || rd != sizeof(eh.eh32))
		{
			fprintf(stderr, "Can't read the file %s\n", argv[1]);
			exit(98);
		}
	}
	file_header_1(eh);
	file_header_2(eh);
	close(fd);
	return (0);
}

/**
 * file_header_1 - Sends the function to validate
 * @eh: Pointer to the ELF eh
 *
 * Return: Nothing
 */
void file_header_1(elf eh)
{
	char *str = NULL;

	check_elf(eh);

	magic_number(eh);

	str = class_file(eh);
	printer_file_header("Class", str, 0);

	str = data(eh);
	printer_file_header("Data", str, 0);

	str = version_0(eh);
	printer_file_header("Version", str, 0);

	str = os_abi(eh);
	printer_file_header("OS/ABI", str, 0);

	str = abi_version(eh);
	printer_file_header("ABI Version", str, 0);

	str = type(eh);
	printer_file_header("Type", str, 0);

	str = machine(eh);
	printer_file_header("Machine", str, 0);

	str = version_1(eh);
	printer_file_header("Version", str, 1);

	str = point_address(eh);
	printer_file_header("Entry point address", str, 1);

	str = start_program_headers(eh);
	printer_file_header("Start of program headers", str, 2);

	str = start_section_headers(eh);
	printer_file_header("Start of section headers", str, 2);
}

/**
 * file_header_2 - Sends the function to validate
 * @header: Pointer to the ELF header
 *
 * Return: Nothing
 */
void file_header_2(elf header)
{
	char *str = NULL;

	str = flags(header);
	printer_file_header("Flags", str, 1);

	str = header_size(header);
	printer_file_header("Size of this header", str, 3);

	str = program_header_size(header);
	printer_file_header("Size of program headers", str, 3);

	str = program_headers_number(header);
	printer_file_header("Number of program headers", str, 0);

	str = section_headers_size(header);
	printer_file_header("Size of section headers", str, 3);

	str = section_headers_number(header);
	printer_file_header("Number of section headers", str, 0);

	str = section_headers_index(header);
	printer_file_header("Section header string table index", str, 0);
}

/**
 * printer_file_header - Prints in file header order format
 * @key: Key to insert
 * @value: Value to insert
 * @type: Type of format to add
 *
 * Return: Nothing
 */
void printer_file_header(char *key, char *value, char type)
{
	int i = 0;

	putchar(0x20);
	putchar(0x20);
	printf("%s", key);
	putchar(0x3a);
	for (i = 34 - _strlen(key); i > 0; i--)
	{
		putchar(0x20);
	}
	if (type == 1)
	{
		putchar(0x30);
		putchar(0x78);
	}
	printf("%s", value);
	if (type == 2)
		printf(" (bytes into file)");
	if (type == 3)
		printf(" (bytes)");
	putchar(0xa);
}
