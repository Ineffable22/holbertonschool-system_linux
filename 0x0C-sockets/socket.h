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

/* ----- server.c -----*/
int start_server(void);
int accept_message(const int sockid);
int response(int fd, char *buf);
void die_with_error(const char *str, const int sockid);

/* ----- server.c -----*/

#endif /* _SOCKET_H_ */
