# GNU Compiler Collection
CC = gcc
# Debugging memory problems and program performance
VAL = valgrind
# GNU Debugger
GDB = gdb

# C flags
CFLAGS = -Wall -Werror -Wextra -pedantic
# GDB flag
GFLAG = -g
# Valgrind flags
VFLAGS = --tool=memcheck --track-origins=yes --leak-check=full --show-leak-kinds=all -s

# Betty C99
BETTY = betty
# All C files
SRC = *.c
# All C headers
HEADER = *.h

# Command readelf
RELF = readelf
# readelf flags
EFLAG0 = -W -h
EFLAG1 = -W -S
EFLAG2 = -W -l
EFLAG3 = -W -s

# Task0
SRC0 = file_header*.c holbie_tools.c
NAME0 = 0-hreadelf

# Task1
SRC1 = section_header*.c holbie_tools.c
NAME1 = 1-hreadelf

# Task2
SRC2 = program_header*.c holbie_tools.c
NAME2 = 2-hreadelf

# Task3
SRC3 = section_header*.c holbie_tools.c
NAME3 = 100-hreadelf

# Optional ARGS="ELF file"

all: clean *.c *.h

# Task 0 File Header
0-hreadelf: all
	$(CC) $(SRC0) $(CFLAGS) $(GFLAG) -o $(NAME0)
run0: 0-hreadelf
	./$(NAME0) $(ARGS)
test0: 0-hreadelf
	./$(NAME0) $(ARGS)
	$(RELF) $(EFLAG0) $(ARGS)

# Task 1 Section Header
1-hreadelf: all
	$(CC) $(SRC1) $(CFLAGS) $(GFLAG) -o $(NAME1)
run1: 1-hreadelf
	./$(NAME1) $(ARGS)
test1: 1-hreadelf
	./$(NAME1) $(ARGS)
	$(RELF) $(EFLAG1) $(ARGS)

# Task 2  Program Headers
2-hreadelf: all
	$(CC) $(SRC2) $(CFLAGS) $(GFLAG) -o $(NAME2)
run2: 2-hreadelf
	./$(NAME2) $(ARGS)
test2: 2-hreadelf
	./$(NAME2) $(ARGS)
	$(RELF) $(EFLAG2) $(ARGS)

# Task 3 Symbol Tables
100-hreadelf: all
	$(CC) $(SRC3) $(CFLAGS) $(GFLAG) -o $(NAME3)
run3: 100-hreadelf
	./$(NAME3) $(ARGS)
test3: 100-hreadelf
	./$(NAME3) $(ARGS)
	$(RELF) $(EFLAG3) $(ARGS)

# Tools
val: 0-hreadelf 1-hreadelf 2-hreadelf 100-hreadelf
	$(VAL) $(VFLAGS) ./$(ARGS)
gdb: 0-hreadelf 1-hreadelf 2-hreadelf 100-hreadelf
	$(GDB) ./$(ARGS)
betty:
	$(BETTY) $(SRC) $(HEADER)
clean:
	$(RM) *~ $(NAME0) $(NAME1) $(NAME2) $(NAME3)
