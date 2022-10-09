#include "signals.h"

/**
 * handle_all_signal - Prints when signal is called
 * @sig: The number of the signal that caused invocation of the handler.
 * @info: A pointer to a siginfo_t, which is a structure containing
 * further information about the signal, as described below.
 * @ucontext: A pointer to a ucontext_t structure
 *
 * Return: Nothing
 */
void handle_all_signal(int sig, siginfo_t *info, void *ucontext)
{
	(void) sig;
	(void) ucontext;
	psiginfo(info, "Caught");
}

/**
 * all_in_one - Sets up a single handler for all the signals
 *
 * Return: Nothing
 **/
void all_in_one(void)
{
	struct sigaction act;
	int i = 1;

	act.sa_flags |= SA_SIGINFO;
	act.sa_sigaction = handle_all_signal;
	for (; i < SIGRTMIN; i++)
	{
		if (i != SIGKILL && i != SIGSTOP)
			sigaction(i, &act, NULL);
	}
}
