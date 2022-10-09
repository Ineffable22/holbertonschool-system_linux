#include "signals.h"

/**
 * print_hello - Prints when signal is called
 * @signal: Signal number that was caught
 *
 * Return: Nothing
 */
void print_hello(int signal)
{
	(void) signal;
	printf("Hello :)\n");
	fflush(stdout);
}

/**
 * set_print_hello - Set a handler for the signal SIGINT
 *
 * Return: 0 on success, or -1 on error
 */
int set_print_hello(void)
{
	struct sigaction act;

	act.sa_handler = print_hello;
	return (sigaction(SIGINT, &act, NULL));
}
