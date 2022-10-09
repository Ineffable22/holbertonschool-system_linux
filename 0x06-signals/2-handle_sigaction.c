#include "signals.h"

/**
 * sigint - Prints when signal is called
 * @signal: Signal number that was caught
 *
 * Return: Nothing
 */
void sigint(int signal)
{
	printf("Gotcha! [%d]\n", signal);
	fflush(stdout);

}

/**
 * handle_sigaction - Set a handler for the signal SIGINT
 *
 * Return: 0 on success, or -1 on error
 */
int handle_sigaction(void)
{
	struct sigaction act;

	act.sa_handler = sigint;
	return (sigaction(SIGINT, &act, NULL));
}
