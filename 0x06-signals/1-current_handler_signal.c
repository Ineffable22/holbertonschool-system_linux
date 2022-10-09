#include "signals.h"

/**
 * current_handler_signal - Retrieves the current handler of the signal SIGINT
 *
 * Return: A pointer to the current handler of SIGINT, or NULL on failure
 */
void (*current_handler_signal(void))(int)
{
	sighandler_t handler;

	handler = signal(SIGINT, SIG_IGN);
	if (handler == SIG_ERR)
		return (NULL);

	if (signal(SIGINT, handler) == SIG_ERR)
		return (NULL);
	return (handler);
}
