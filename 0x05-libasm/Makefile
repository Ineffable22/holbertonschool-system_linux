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

# Tools
clean:
	$(RM) *~ $(AOBJ) $(AC)
