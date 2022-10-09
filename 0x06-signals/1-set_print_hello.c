#include "signals.h"

/**
 * print_hello - Prints when signal is called
 * @signum: Signal number that was caught
 *
 * Return: Nothing
 */
void print_hello(int signum)
{
	printf("Gotcha! [%d]\n", signum);
}

/**
 * set_print_hello - Set a handler for the signal SIGINT
 *
 * Return: 0 on success, or -1 on error
 */
int set_print_hello(void)
{
	if (signal(SIGINT, print_hello) == SIG_ERR)
		return (-1);
	return (0);
}
