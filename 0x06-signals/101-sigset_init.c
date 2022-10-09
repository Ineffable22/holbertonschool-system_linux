#include "signals.h"

/**
 * sigset_init - Initializes a sigset
 * @set: Is a pointer to the signal set to initialize
 * @signals: Is a 0-terminated array of int, each one being a signal number
 *
 * Return: 0 on success, or -1 on error
 */
int sigset_init(sigset_t *set, int *signals)
{
	for (sigemptyset(set); *signals; signals++)
		if (sigaddset(set, *signals))
			return (-1);
	return (0);
}
