# GNU Compiler Collection
CC = gcc
# C flags
CFLAGS = -c -Wall -Werror -Wextra -pedantic
# All C files
SRC = *.c
# All C Object files
OBJ = *.o

# Netwide Assembler
NASM = nasm
# ASM flags
AFLAGS = -f elf64
# All Assembly files
ASM = *.asm

# Executable file name
NAME = a.out

# Optional ARGS="ELF file"
all: clean *.asm *.c run

# Task 0 File Header
run:
	$(NASM) $(AFLAGS) $(ASM)
	$(CC) $(CFLAGS) $(SRC)
	$(CC) $(OBJ)

# Tools
clean:
	$(RM) *~ $(NAME) $(OBJ)
