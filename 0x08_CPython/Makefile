CC = gcc
CFLAGS = -Wall -Werror -Wextra -pedantic -std=c99 -shared -Wl,-soname,PyList -o libPyList.so -fPIC -I/usr/include/python3.11
CFILES = *.c
PYFILES = *.py
NAME1 = 1-python.c
TEST1 = 1-test_lists.py

1: *.c clean
	cp test/$(TEST1) .
	$(CC) $(CFLAGS) $(NAME1)
	python3 $(TEST1)
	rm $(TEST1)

success: betty pep8

betty:
	betty $(CFILES)

pep8:
	pycodestyle test/$(PYFILES)

clean:
	rm -f *~ $(TEST1)
