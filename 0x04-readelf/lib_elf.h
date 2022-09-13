#ifndef _lib_ELF_H_
#define _lib_ELF_H_

#include <elf.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>


void check_elf(Elf64_Ehdr *header);
void osabi(Elf64_Ehdr *header);
void machine(Elf64_Ehdr *header);
void version(Elf64_Ehdr *header);
void number(Elf64_Ehdr *header);

#endif
