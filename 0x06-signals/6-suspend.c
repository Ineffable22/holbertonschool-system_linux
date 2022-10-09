#include "signals.h"

/**
 * handle_sigint - Prints when signal is called
 * @signal: Signal number that was caught
 *
 * Return: Nothing
 */
void handle_sigint(int signal)
{
	printf("Caught %d\n", signal);
	fflush(stdout);
}

/**
 * main - Sets a handler for the signal SIGINT, and exits
 * right after the signal is received and handled
 *
 * Return: EXIT_SUCCESS or EXIT_FAILURE
 **/
int main(void)
{
	struct sigaction act;

	act.sa_handler = handle_sigint;
	if (sigaction(SIGINT, &act, NULL) == -1)
		return (EXIT_FAILURE);
	pause();
	printf("Signal received\n");
	return (EXIT_SUCCESS);
}
