#ifndef _GETLINE_H
#define _GETLINE_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define READ_SIZE 1024

/**
 * struct Superbuffer - Struct that stores all the flags in the stream.
 * This structure was invoked as static.
 * @buff: Is a pointer that stores everything read by position.
 * @data: Is a pointer with flags to create_stream function
 * @next: Pointer to the next node in the struct Superbuffer
 */
typedef struct Superbuffer
{
	char *buff;
	int *data;
	struct Superbuffer *next;
} supabuffa;

char *_getline(const int fd);

#endif
