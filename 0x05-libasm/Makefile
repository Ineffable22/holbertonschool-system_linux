# GNU Compiler Collection
CC = gcc
# C flags
CFLAGS = -Wall -Wextra -Werror -pedantic -g3 -c
# All C files
AC = *.c
# All C Object files
AOBJ = *.o
# Main name
SRC = -main

# C files
ENDC = .c
# Object files
OBJ = .o

# Directory
FILE = files/
# Change name flag
OFLAG = -o

# Netwide Assembler
NASM = nasm
# ASM flags
AFLAGS = -f elf64
# All Assembly files
ASM = .asm
# Copy
CP = cp
# Current directory
DOT = .

# Optional NUMBER="ELF file"
all: clean *.asm files/*.c run

# Task 0 File Header
run:
	$(CP) $(FILE)$(NUMBER)$(SRC)$(ENDC) $(DOT)
	$(CC) $(CFLAGS) $(OFLAG) $(NUMBER)$(SRC)$(OBJ) $(NUMBER)$(SRC)$(ENDC)
	$(NASM) $(AFLAGS) $(OFLAG) $(NUMBER)$(NAME)$(OBJ) $(NUMBER)$(NAME)$(ASM)
	$(CC) $(OFLAG) $(NUMBER)$(NAME) $(AOBJ)
	./$(NUMBER)$(NAME)
	$(RM) *~ $(NUMBER)$(NAME) $(AOBJ) $(AC)

7:
	gcc -Wall -Wextra -Werror -pedantic -g3 -c -o 7-main.o 7-main.c
	nasm -f elf64 -o 7-puts.o 7-puts.asm
	nasm -f elf64 -o 0-strlen.o 0-strlen.asm
	gcc -o 7-puts 7-main.o 7-puts.o 0-strlen.o
	./7-puts 

100:
	cp files/100-main.c .
	gcc -Wall -Wextra -Werror -pedantic -g3 -c -o 100-main.o 100-main.c
	nasm -f elf64 -o 100-puti.o 100-puti.asm
	nasm -f elf64 -o 6-putc.o 6-putc.asm
	gcc -o 100-puti 100-main.o 100-puti.o 6-putc.o
	./100-puti 
	rm 100-puti *.o *.c

101:
	cp files/101-main.c .
	gcc -Wall -Wextra -Werror -pedantic -g3 -c -o 101-main.o 101-main.c
	nasm -f elf64 -o 101-puti_base.o 101-puti_base.asm
	nasm -f elf64 -o 6-putc.o 6-putc.asm
	nasm -f elf64 -o 0-strlen.o 0-strlen.asm
	gcc -o 101-puti_base 101-main.o 101-puti_base.o 6-putc.o 0-strlen.o
	./101-puti_base 
	rm 101-puti_base *.o *.c

# Tools
clean:
	$(RM) *~ $(AOBJ) $(AC)

betty:
	betty *.asm