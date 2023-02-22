#include "socket.h"

/**
 * die_with_error - Print message to stderr and exit
 * @str:    String to print
 * @sockid: Socket descriptor to close
 *
 * Returns: Nothing
 */
void die_with_error(char *str, int sockid)
{
	fprintf(stderr, "%s\n", str);
	if (close(sockid) == -1)
		fprintf(stderr, "close error\n");
	exit(EXIT_FAILURE);
}

/**
 * create_socket - Create a socket
 *
 * Return: A new socket
 */
int create_socket(void)
{
	int sockid;

	sockid = socket(PF_INET, SOCK_STREAM, 0);
	if (sockid == -1)
	{
		fprintf(stderr, "socket error\n");
		return (-1);
	}
	return (sockid);
}

/**
 * main - Connects to a listening server
 * @argc: Number of arguments
 * @argv: Command line arguments
 *
 * Return: EXIST_SUCCESS on success, EXIST_FAIL on failure
 */
int main(int argc, char **argv)
{
	struct sockaddr_in servAddr;
	int sockid, status;

	if (argc != 3)
	{
		printf("Usage: %s <host> <port>\n", argv[0]);
		return (EXIT_FAILURE);
	}
	sockid = create_socket();
	if (sockid == -1)
		exit(EXIT_FAILURE);
	servAddr.sin_family = AF_INET;
	servAddr.sin_port = htons(atoi(argv[2]));
	status = connect(sockid, (struct sockaddr *)&servAddr, sizeof(servAddr));
	if (status == -1)
		die_with_error("connect error", sockid);
	printf("Connected to %s:%s\n", argv[1], argv[2]);
	return (EXIT_SUCCESS);
}
