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

5:
	$(CC) $(CFLAGS) test/21-main.c 21-prime_factors.c list.c -o 21-prime_factors
	./21-prime_factors 745 872346 79283472974
	./21-prime_factors 1048576
	./21-prime_factors 18446744073709551612 18446744073709551609 18446744073709551608
	rm 21-prime_factors

betty:
	betty --allow-global-variables *.c *.h test/*.c

