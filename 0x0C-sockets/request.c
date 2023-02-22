#include "socket.h"

/**
 * main - Opens an IPv4/TCP socket, and listens to traffic on port 8080
 *
 * Return: Always EXIT_SUCCESS
*/
int main(void)
{
	start_server();
	return (EXIT_SUCCESS);
}
