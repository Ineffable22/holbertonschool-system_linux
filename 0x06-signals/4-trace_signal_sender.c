#include "signals.h"

/**
 * handle_sigquit - Prints when signal is called
 * @sig: The number of the signal that caused invocation of the handler.
 * @info: A pointer to a siginfo_t, which is a structure containing
 * further information about the signal, as described below.
 * @ucontext: A pointer to a ucontext_t structure
 *
 * Return: Nothing
 */
void handle_sigquit(int sig, siginfo_t *info, void *ucontext)
{
	(void) sig;
	(void) ucontext;
	printf("SIGQUIT sent by [%d]\n", info->si_pid);
}


/**
 * trace_signal_sender - Defines a handler for the signal SIGQUIT
 * (Control-\ in a shell)
 *
 * Return: 0 on success, or -1 on error
 */
int trace_signal_sender(void)
{
	struct sigaction act;

	act.sa_sigaction = handle_sigquit;
	return (sigaction(SIGQUIT, &act, NULL) == -1);
}
