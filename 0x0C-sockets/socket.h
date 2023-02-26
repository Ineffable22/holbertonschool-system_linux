#ifndef _SOCKET_H_
#define _SOCKET_H_

#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <signal.h>

#define PORT 8080
#define CRLF "\r\n"

/**
 * struct memory_s - Structure representing a memory allocation
 * @id: identifier
 * @key_query: Key of first query
 * @value_query: Value of first query
 * @key_query2: Key of second query
 * @value_query2: Value of second query
 * @next: Pointer to next structure
 */
typedef struct memory_s
{
	int id[BUFSIZ];
	char *key_query[BUFSIZ];
	char *value_query[BUFSIZ];
	char *key_query2[BUFSIZ];
	char *value_query2[BUFSIZ];
	struct memory_s *next;
} memory_t;

extern int server_fd;
extern int client_fd;
extern char ram_json[100][100];
extern int id;

/* ----- server.c -----*/
int start_server(int task);
int accept_message(int task);
void die_with_error(const char *str);
void response_signal(int x);

/* ----- {4..11}-*.c -----*/
int response(char *buf);

/* ----- status_code.c -----*/
int http_response(const int status_code);
char *get_response(const int status_code);

#endif /* _SOCKET_H_ */
