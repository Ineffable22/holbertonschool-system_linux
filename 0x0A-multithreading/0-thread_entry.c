#include "multithreading.h"

/**
 * thread_entry - Serve as the entry point to a new thread.
 * @arg: A string that must be printed and followed by a new line.
 *
 * Return: Nothing
 */
void *thread_entry(void *arg)
{
	printf("%s\n", (char *)arg);
	pthread_exit(NULL);
}
