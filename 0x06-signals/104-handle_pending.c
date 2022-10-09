#include "signals.h"

/**
 * handle_pending - Sets up a handler for all the pending signals
 * of the current process
 * @handler: Is a pointer to the handler function to set for the
 * pending signals
 *
 * Return: 0 on success, or -1 on error
 */
int handle_pending(void (*handler)(int))
{
	sigset_t signal_set;
	struct sigaction act;
	int i = 0;

	if (sigemptyset(&signal_set) == -1)
		return (-1);
	if (sigpending(&signal_set) == -1)
		return (-1);

	act.sa_handler = handler;
	for (i = 1; i < SIGRTMIN; i++)
	{
		if (sigismember(&signal_set, i) && i != SIGKILL && i != SIGSTOP)
			if (sigaction(i, &act, NULL) == -1)
				return (-1);
	}
	return (0);
}
