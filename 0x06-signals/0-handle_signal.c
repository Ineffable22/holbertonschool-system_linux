#include "signals.h"

/**
 * handle_sigint - Prints when signal is called
 * @signum: Signal number that was caught
 *
 * Return: Nothing
 */
void handle_sigint(int signum)
{
	printf("Gotcha! [%d]\n", signum);
	fflush(stdout);
}

/**
 * handle_signal - Set a handler for the signal SIGINT
 *
 * Return: 0 on success, or -1 on error
 */
int handle_signal(void)
{
	if (signal(SIGINT, handle_sigint) == SIG_ERR)
		return (-1);
	return (0);
}
