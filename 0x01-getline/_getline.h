#ifndef _GETLINE_H
#define _GETLINE_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define READ_SIZE 500

char *_getline(const int fd);

#endif
