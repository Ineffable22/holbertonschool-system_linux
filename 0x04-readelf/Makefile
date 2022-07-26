# GNU Compiler Collection
CC = gcc
# C flags
CFLAGS = -Wall -Werror -Wextra -pedantic

# GNU Debugger
GDB = gdb
# GDB flag
GFLAG = -g

# Debugging memory problems and program performance
VAL = valgrind
# Valgrind flags
VFLAGS = --tool=memcheck --track-origins=yes --leak-check=full --show-leak-kinds=all -s

# Comparator
CMP = compare_files.c
# Betty C99
BETTY = betty
# All C files
SRC = *.c
# All C headers
HEADER = *.h

# Command readelf
RELF = readelf
ELF_FILE = a.out solaris32 sortix32 sparcbigendian32 ubuntu64 jpeg.mod python.obj libperl.so.5.18 sftp-server vgpreload_memcheck-x86-linux.so netbsd32

# readelf flags
EFLAG0 = -W -h
EFLAG1 = -W -S
EFLAG2 = -W -l
EFLAG3 = -W -s

# Task0
SRC0 = file_header*.c holbie_tools.c endians.c
NAME0 = 0-hreadelf

# Task1
SRC1 = section_header*.c file_header_*.c holbie_tools.c
NAME1 = 1-hreadelf

# Task2
SRC2 = program_header*.c file_header_*.c holbie_tools.c
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
	cp test/$(ARGS) .
	./$(NAME0) $(ARGS)
	$(RELF) $(EFLAG0) $(ARGS)
	rm $(ARGS) $(NAME0)
test0: 0-hreadelf
	cp test/$(ARGS) .
	./$(NAME0) $(ARGS) > text1
	$(RELF) $(EFLAG0) $(ARGS) > text2
	rm $(ARGS) $(NAME0)
	$(CC) $(CMP) $(CFLAGS)
	./a.out
	rm a.out text1 text2
all0: 0-hreadelf
	$(foreach var,$(ELF_FILE), cp test/$(var) .; ./$(NAME0) $(var) > text1; $(RELF) $(EFLAG0) $(var) > text2; rm $(var); $(CC) $(CMP) $(CFLAGS); ./a.out; rm a.out text1 text2;)
	rm $(NAME0)

# Task 1 Section Header
1-hreadelf: all
	$(CC) $(SRC1) $(CFLAGS) $(GFLAG) -o $(NAME1)
run1: 1-hreadelf
	cp test/$(ELF_FILE) .
	./$(NAME1) $(ELF_FILE)
	rm $(ELF_FILE) $(NAME1)
test1: 1-hreadelf
	./$(NAME1) $(ELF_FILE)
	$(RELF) $(EFLAG1) $(ELF_FILE)

# Task 2  Program Headers
2-hreadelf: all
	$(CC) $(SRC2) $(CFLAGS) $(GFLAG) -o $(NAME2)
run2: 2-hreadelf
	cp test/$(ELF_FILE) .
	./$(NAME2) $(ELF_FILE)
	rm $(ELF_FILE) $(NAME2)
test2: 2-hreadelf
	./$(NAME2) $(ELF_FILE)
	$(RELF) $(EFLAG2) $(ELF_FILE)

# Task 3 Symbol Tables
100-hreadelf: all
	$(CC) $(SRC3) $(CFLAGS) $(GFLAG) -o $(NAME3)
run3: 100-hreadelf
	cp test/$(ELF_FILE) .
	./$(NAME3) $(ELF_FILE)
	rm $(ELF_FILE) $(NAME3)
test3: 100-hreadelf
	./$(NAME3) $(ELF_FILE)
	$(RELF) $(EFLAG3) $(ELF_FILE)

# Tools
val: 0-hreadelf 1-hreadelf 2-hreadelf 100-hreadelf
	$(VAL) $(VFLAGS) ./$(ELF_FILE)
gdb: 0-hreadelf 1-hreadelf 2-hreadelf # 100-hreadelf
	$(GDB) ./$(ELF_FILE)
betty:
	$(BETTY) $(SRC) $(HEADER)
clean:
	$(RM) *~ $(NAME0) $(NAME1) $(NAME2) $(NAME3)
