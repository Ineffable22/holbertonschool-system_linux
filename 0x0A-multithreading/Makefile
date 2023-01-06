CC = gcc
CFLAGS = -Wall -Wextra -Werror -pedantic -g3 -pthread -I ./

0:
	$(CC) $(CFLAGS) test/0-main.c 0-thread_entry.c -o 0-thread_entry
	./0-thread_entry
	rm 0-thread_entry

1:
	$(CC) $(CFLAGS) test/1-main.c 1-tprintf.c -o 1-tprintf
	./1-tprintf
	rm 1-tprintf

2:
	$(CC) $(CFLAGS) test/10-main.c 10-blur_portion.c -o 10-blur_portion
	./10-blur_portion images/car.pbm images/kernel_0.knl
	rm 10-blur_portion

3:
	$(CC) $(CFLAGS) test/11-main.c 11-blur_image.c 10-blur_portion.c -o 11-blur_image -pthread
	time ./11-blur_image images/car.pbm images/kernel_0.knl
	rm 11-blur_image

4:
	$(CC) $(CFLAGS) test/20-main.c 1-tprintf.c -o 20-tprintf -pthread
	./20-tprintf
	rm 20-tprintf
4.1:
	$(CC) $(CFLAGS) test/20-main.c 20-tprintf.c -o 20-tprintf -pthread
	./20-tprintf
	rm 20-tprintf

betty:
	betty --allow-global-variables *.c *.h test/*.c

