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
 * Return: Always 0
 */
int tprintf(char const *format, ...)
{
	pthread_mutex_lock(&mutex);
	printf("[%lu] %s", pthread_self(), format);
	pthread_mutex_unlock(&mutex);
	return (0);
}
