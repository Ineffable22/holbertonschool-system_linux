#include "socket.h"

int client_fd = -1;
int server_fd = -1;
char ram_json[100][100] = {0};
int id = 0;

/**
 * die_with_error - Print message to stderr and exit
 * @str:    String to print
 *
 * Returns: Nothing
 */
void die_with_error(const char *str)
{
	fprintf(stderr, "%s\n", str);
	if (client_fd != -1 && close(server_fd) == -1)
		fprintf(stderr, "close client error\n");
	if (server_fd != -1 && close(server_fd) == -1)
		fprintf(stderr, "close server error\n");
}

/**
 * start_server - Start the server and connect
 *
 * Return: EXIT_SUCCESS if successful otherwise EXIT_FAILURE
 */
int start_server(void)
{
	struct sockaddr_in server;

	signal(SIGINT, response_signal);
	server_fd = socket(PF_INET, SOCK_STREAM, 0);
	if (server_fd == -1)
		return (fprintf(stderr, "socket error\n"), EXIT_FAILURE);
	server.sin_family = AF_INET;
	server.sin_port = htons(PORT);
	server.sin_addr.s_addr = htonl(INADDR_ANY);
	if (bind(server_fd, (struct sockaddr *)&server, sizeof(server)) == -1)
		return (die_with_error("bind error"), EXIT_FAILURE);
	if (listen(server_fd, SOMAXCONN) == -1)
		return (die_with_error("listen error"), EXIT_FAILURE);
	printf("Server listening on port %d\n", PORT);
	while (accept_message() == EXIT_SUCCESS)
	{}
	return (EXIT_SUCCESS);
}

/**
 * response_signal - Close client_fd and server_fd
 * @x: Unused number
 *
 * Return: Nothing
 */
void response_signal(int x)
{
	(void) x;

	if (server_fd != -1 && close(server_fd) == -1)
		fprintf(stderr, "close server error\n");
	server_fd = -1;
	if (client_fd != -1 && close(server_fd) == -1)
		fprintf(stderr, "close client error\n");
	client_fd = -1;
	exit(EXIT_FAILURE);
}

/**
 * accept_message - Accept a message from the server
 *
 * Return: Nothing
 */
int accept_message(void)
{
	char *client_ip, buf[BUFSIZ];
	int rd;
	struct sockaddr_in ClientAddress;
	socklen_t adddrLen = sizeof(ClientAddress);

	client_fd = accept(server_fd, (struct sockaddr *)&ClientAddress, &adddrLen);
	if (client_fd == -1)
		return (die_with_error("accept error"), EXIT_FAILURE);
	client_ip = inet_ntoa(ClientAddress.sin_addr);
	if (client_ip == NULL)
		return (die_with_error("inet_ntoa error"), EXIT_FAILURE);
	printf("Client connected: %s\n", client_ip);
	rd = recv(client_fd, buf, BUFSIZ, 0);
	if (rd == -1)
		return (die_with_error("recv error"), EXIT_FAILURE);
	printf("Raw request: \"%s\"\n", buf);
	return (response(buf));
}
