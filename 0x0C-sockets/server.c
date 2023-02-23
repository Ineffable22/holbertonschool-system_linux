#include "socket.h"

/**
 * die_with_error - Print message to stderr and exit
 * @str:    String to print
 * @sockid: Socket descriptor to close
 *
 * Returns: Nothing
 */
void die_with_error(const char *str, const int sockid)
{
	fprintf(stderr, "%s\n", str);
	if (close(sockid) == -1)
		fprintf(stderr, "close error\n");
}

/**
 * start_server - Start the server and connect
 *
 * Return: A new socket
 */
int start_server(void)
{
	int sockid;
	struct sockaddr_in server;

	sockid = socket(PF_INET, SOCK_STREAM, 0);
	if (sockid == -1)
	{
		fprintf(stderr, "socket error\n");
		return (EXIT_FAILURE);
	}
	server.sin_family = AF_INET;
	server.sin_port = htons(PORT);
	server.sin_addr.s_addr = htonl(INADDR_ANY);
	if (bind(sockid, (struct sockaddr *)&server, sizeof(server)) == -1)
	{
		die_with_error("bind error", sockid);
		return (EXIT_FAILURE);
	}
	if (listen(sockid, SOMAXCONN) == -1)
	{
		die_with_error("listen error", sockid);
		return (EXIT_FAILURE);
	}
	printf("Server listening on port %d\n", PORT);
	while (accept_message(sockid) == EXIT_SUCCESS)
	{}
	return (EXIT_SUCCESS);
}

/**
 * response_signal - Prints the prompt signal (Ctrl + C)
 * @x: Unused number
 *
 * Return: Nothing
 */
void response_signal(int x)
{
	void *ptr;
	int option = 1;
	int sockid;
	(void) x;

	ptr = sbrk(0);
	ptr = (char *)ptr - sizeof(int);
	sockid = *(int *)ptr;
	setsockopt(sockid, SOL_SOCKET, SO_REUSEADDR, &option, sizeof(option));
	close(sockid);
	exit(EXIT_FAILURE);
}

/**
 * accept_message - Accept a message from the server
 * @sockid: Socket descriptor
 *
 * Return: Nothing
 */
int accept_message(const int sockid)
{
	char *client_ip, buf[BUFSIZ];
	int rd, fd;
	struct sockaddr_in ClientAddress;
	socklen_t adddrLen = sizeof(ClientAddress);
	void *ptr;

	signal(SIGINT, response_signal);
	/* Save sockid in memory to close if needed with signal */
	ptr = sbrk(sizeof(int));
	*(int *)ptr = sockid;

	fd = accept(sockid, (struct sockaddr *)&ClientAddress, &adddrLen);
	if (fd == -1)
	{
		die_with_error("accept error", sockid);
		return (EXIT_FAILURE);
	}
	client_ip = inet_ntoa(ClientAddress.sin_addr);
	if (client_ip == NULL)
	{
		die_with_error("inet_ntoa error", sockid);
		return (EXIT_FAILURE);
	}
	printf("Client connected: %s\n", client_ip);
	rd = recv(fd, buf, BUFSIZ, 0);
	if (rd == -1)
	{
		die_with_error("recv error", sockid);
		return (EXIT_FAILURE);
	}
	printf("Raw request: \"%s\"/\n", buf);
	response(fd, buf);
	return (EXIT_SUCCESS);
}
