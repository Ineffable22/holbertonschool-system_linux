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
#define MAX_SIZE 1024

extern int server_fd;
extern int client_fd;
extern char ram_json[MAX_SIZE][MAX_SIZE];
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
char *get_1xx_3xx(const int status_code);
char *get_4xx(const int status_code);
char *get_5xx(const int status_code);

#endif /* _SOCKET_H_ */
