CC = gcc
CFLAGS = -Wall -Wextra -Werror -pedantic
HEADER = socket.h
BETTY = betty

SRC0 = 0-server.c
OBJ0 = $(SRC0:%.c=%.o)
NAME0 = 0-server

SRC1 = 1-server.c
OBJ1 = $(SRC1:%.c=%.o)
NAME1 = 1-server

SRC2 = 2-client.c
OBJ2 = $(SRC2:%.c=%.o)
NAME2 = 2-client

SRC3 = 3-server.c
OBJ3 = $(SRC3:%.c=%.o)
NAME3 = 3-server

SRC4 = server.c request.c
OBJ4 = $(SRC4:%.c=%.o)
NAME4 = todo_api_0

SRC = 
OBJ = $(SRC:%.c=%.o)
NAME =

ALLOBJ = $(OBJ0) $(OBJ1) $(OBJ2) $(OBJ3) $(OBJ4) $(OBJ5) $(OBJ6) $(OBJ7) $(OBJ8) $(OBJ9) $(OBJ10) $(OBJ11)
ALLNAME = $(NAME0) $(NAME1) $(NAME2) $(NAME3) $(NAME4) $(NAME5) $(NAME6) $(NAME7) $(NAME8) $(NAME9) $(NAME10) $(NAME11)

.PHONY: taks0 taks1 taks2 taks3 todo_api_0

all: taks0 taks1 taks2 taks3 todo_api_0

# Task 0-3
task0: $(OBJ0)
	$(CC) $(CFLAGS) $(OBJ0) -o $(NAME0)

task1: $(OBJ1)
	$(CC) $(CFLAGS) $(OBJ1) -o $(NAME1)

task2: $(OBJ2)
	$(CC) $(CFLAGS) $(OBJ2) -o $(NAME2)

task3: $(OBJ3)
	$(CC) $(CFLAGS) $(OBJ3) -o $(NAME3)

# API tasks 4 - 11
todo_api_0: $(HEADER) $(OBJ4)
	$(CC) $(CFLAGS) $(OBJ4) -o $(NAME4)

clean:
	$(foreach var, $(ALLNAME), $(RM) *~ $(var))

oclean:
	$(foreach var, $(ALLOBJ), $(RM) $(var))

fclean: clean oclean

re: oclean all

betty:
	$(BETTY) *.c *.h
