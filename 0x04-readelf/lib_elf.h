#ifndef _lib_ELF_H_
#define _lib_ELF_H_

#include <elf.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define CHECK_64(x) ((x).e_ident[EI_CLASS] == ELFCLASS64)
#define IS_BE(x) ((x).e_ident[EI_DATA] == ELFDATA2MSB)
#define EGET(x) (CHECK_64(eh.eh64) ? eh.eh64.x : eh.eh32.x)

/* ----- Structures ----- */
/**
 * struct Elf - struct with types of architectures
 * @eh64: Elf header 64 bits
 * @eh32: Elf header 32 bits
 */
typedef struct Elf
{
	Elf64_Ehdr eh64;
	Elf32_Ehdr eh32;
} elf;


/* ----- file_header.c ----- */
void file_header_1(elf header);
void file_header_2(elf header);
void printer_file_header(char *key, char *value, char type);

/* ----- file_header_1.c ----- */
void check_elf(elf header);
void magic_number(elf header);
char *class_file(elf header);
char *data(elf header);
char *version_0(elf header);

/* ----- file_header_2.c ----- */
char *os_abi(elf header);
char *abi_version(elf header);
char *type(elf header);
char *machine(elf header);
char *version_1(elf header);

/* ----- file_header_3.c ----- */
char *point_address(elf header);
char *start_program_headers(elf header);
char *start_section_headers(elf header);
char *flags(elf header);
char *header_size(elf header);

/* ----- file_header_4.c ----- */
char *program_header_size(elf header);
char *program_headers_number(elf header);
char *section_headers_size(elf header);
char *section_headers_number(elf header);
char *section_headers_index(elf header);

/* ----- section_header_1.c ----- */
void section_header_1(Elf64_Ehdr *ehdr);
void section_header_2(Elf64_Shdr *shdr, Elf64_Ehdr *ehdr, int len, int fd);


/* ----- program_header_1.c ----- */
int program_header_1(Elf64_Ehdr *header);
void program_header_2(Elf64_Phdr *phdr, int len);
void program_header_3(Elf64_Shdr *shdr, int len, int fd, Elf64_Ehdr *ehdr);
char *program_header_name(char *num);
void printer_program_header(Elf64_Phdr phdr);
char *ptype(int type);



/* ----- holbie_tools.c ----- */
int _strlen(char *s);
int _strcmp(char *s1, char *s2);
char *itoa(int val, int base);
int process_ehdr(elf *header, char *filename);




#endif
