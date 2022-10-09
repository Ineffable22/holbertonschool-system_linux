#include "signals.h"

/**
 * signals_block - Block a given set of signals from being delivered
 * to the current process
 * @signals: Is a 0-terminated array of int, each one being a signal to block
 *
 * Return: 0 on success, or -1 on error
 */
int signals_block(int *signals)
{
	sigset_t signal_set;

	if (sigemptyset(&signal_set) == -1)
		return (-1);
	for (; *signals; signals++)
		if (sigaddset(&signal_set, *signals))
			return (-1);
	if (sigprocmask(SIG_BLOCK, &signal_set, NULL) == -1)
		return (-1);
	return (0);
}
