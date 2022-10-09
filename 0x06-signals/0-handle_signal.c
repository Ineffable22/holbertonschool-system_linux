#include "signals.h"

/**
 * sigint - Prints when signal is called
 * @signum: Signal number that was caught
 *
 * Return: Nothing
 */
void sigint(int signum)
{
	printf("Gotcha! [%d]\n", signum);
}

/**
 * handle_signal - Set a handler for the signal SIGINT
 *
 * Return: 0 on success, or -1 on error
 */
int handle_signal(void)
{
	if (signal(SIGINT, sigint) == SIG_ERR)
		return (-1);
	return (0);
}
