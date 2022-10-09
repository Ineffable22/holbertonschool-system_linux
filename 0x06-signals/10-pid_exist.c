#include <signal.h>

/**
 * pid_exist - Tests if a process exists, given its PID
 * @pid: Process ID to identify
 *
 * Return: 1 if the process with the PID pid exists, or 0 otherwise
 */
int pid_exist(pid_t pid)
{
	return (!kill(pid, 0));
}
