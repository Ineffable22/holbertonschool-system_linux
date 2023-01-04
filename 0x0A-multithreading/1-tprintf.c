#include "multithreading.h"

/**
* tprintf - Uses the printf family to print out a given formatted string.
* The output must be preceded by the calling thread ID,
* as the following output shows.
* @format: String to print
*
* Return: Always 0
*/
int tprintf(char const *format, ...)
{
	printf("[%lu] %s", pthread_self(), format);
	return (0);
}
