#include "socket.h"

/**
 * main - Opens an IPv4/TCP socket, and listens to traffic on port 8080
 * - Accept an entering connection
 * - Print the IP address of the connected client
 * - Wait for an incoming message from the connected client
 * - Print the full received HTTP request
 * - Print the break-down of the first line of the received HTTP request (See example)
 * - Send back a response to the connected client (HTTP 200 OK)
 * - Close the connection with the client
 * - Wait for the next connection
 * 
 * Return: Always EXIT_SUCCESS
*/
int main(void)
{
	start_server();
	return (EXIT_SUCCESS);
}

/**
 * response - Print and send HTTP response
 * @fd: file descriptor
 * @buf: buffer to split and print
 *
 * Return: Always EXIT_SUCCESS
 */
int response(int fd, char *buf)
{
	char *method, *path, *version;
	char *delim = " \r\t\n";

	method = strtok(buf, delim);
	path = strtok(NULL, delim);
	version = strtok(NULL, delim);
	printf("Method: %s\n", method);
	printf("Path: %s\n", path);
	printf("Version: %s\n", version);
	send(fd, "HTTP/1.1 200 OK\r\n\r\n", 17, 0);
	return (EXIT_SUCCESS);
}
