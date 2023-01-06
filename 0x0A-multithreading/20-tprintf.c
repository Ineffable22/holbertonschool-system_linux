#include "multithreading.h"
static pthread_mutex_t mutex;

/**
 * begin - initializes global mutex for printf buffer before main
 */
void begin(void)
{
	pthread_mutex_init(&mutex, NULL);
}


/**
 * end - destroys global mutex for printf buffer after main
 */
void end(void)
{
	pthread_mutex_destroy(&mutex);
}

/**
 * tprintf - Print out a given formatted string
 * The output must be preceded by the calling thread ID,
 * as the following output shows.
 * @format: String to print
 *
 * Return: Always 0, otherwise -1 if failed
 */
int tprintf(char const *format, ...)
{
	int len = 0;

	if (!format)
		return (-1);
	pthread_mutex_lock(&mutex);
	printf("[%lu] ", pthread_self());
	len = printf("%s", format);
	pthread_mutex_unlock(&mutex);
	return (len);
}
