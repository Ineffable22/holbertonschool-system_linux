#ifndef _lib_ELF_H_
#define _lib_ELF_H_

#include <elf.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

/* -----  ----- */

/* ----- file_header.c ----- */
void file_header_1(Elf64_Ehdr *header);
void file_header_2(Elf64_Ehdr *header);
void printer_file_header(char *key, char *value, char type);

/* ----- file_header_1.c ----- */
void check_elf(Elf64_Ehdr *header);
void magic_number(Elf64_Ehdr *header);
char *class_file(Elf64_Ehdr *header);
char *data(Elf64_Ehdr *header);
char *version_0(Elf64_Ehdr *header);

/* ----- file_header_2.c ----- */
char *os_abi(Elf64_Ehdr *header);
char *abi_version(Elf64_Ehdr *header);
char *type(Elf64_Ehdr *header);
char *machine(Elf64_Ehdr *header);
char *version_1(Elf64_Ehdr *header);

/* ----- file_header_3.c ----- */
char *point_address(Elf64_Ehdr *header);
char *start_program_headers(Elf64_Ehdr *header);
char *start_section_headers(Elf64_Ehdr *header);
char *flags(Elf64_Ehdr *header);
char *header_size(Elf64_Ehdr *header);

/* ----- file_header_4.c ----- */
char *program_header_size(Elf64_Ehdr *header);
char *program_headers_number(Elf64_Ehdr *header);
char *section_headers_size(Elf64_Ehdr *header);
char *section_headers_number(Elf64_Ehdr *header);
char *section_headers_index(Elf64_Ehdr *header);

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
int process_ehdr(Elf64_Ehdr **header, char *filename);




#endif
