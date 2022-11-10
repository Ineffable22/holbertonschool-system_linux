#ifndef _lib_elf_H_
#define _lib_elf_H_

#include <elf.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

#define CHECK_64(x) ((x).e_ident[EI_CLASS] == ELFCLASS64)
#define IS_BE(x) ((x).e_ident[EI_DATA] == ELFDATA2MSB)
#define EGET(x) (CHECK_64(ep->eh64) ? ep->eh64.x : ep->eh32.x)
#define SGET(i, x) (CHECK_64(ep->eh64) ? ep->sh64[i].x : ep->sh32[i].x)
#define PGET(i, x) (CHECK_64(ep->eh64) ? ep->ph64[i].x : ep->ph32[i].x)
#define YGET(i, x) (CHECK_64(ep->eh64) ? ep->sym64[i].x : ep->sym32[i].x)

typedef struct Elf
{
	Elf64_Ehdr eh64;
	Elf32_Ehdr eh32;
	Elf64_Shdr *sh64;
	Elf32_Shdr *sh32;
	Elf64_Phdr *ph64;
	Elf32_Phdr *ph32;
	Elf32_Sym *sym32;
	Elf64_Sym *sym64;
} elf;

/* ----- main.c ----- */
int process_ehdr(elf *ep, char *filename);
void check_elf(elf *ep);

/* ----- symbol.c.c ----- */
void symbol_1(elf *ep, int fd, char *filename);
void symbol_2(elf *ep);

/* ----- endians.c ----- */
void switch_endians(elf *ep);
unsigned long switch_endian8(unsigned long n);
unsigned int switch_endian4(unsigned int n);
unsigned short switch_endian2(unsigned short n);

#endif
