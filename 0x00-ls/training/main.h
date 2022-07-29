#ifndef MAIN_H
#define MAIN_H

#include <dirent.h>
#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

void types(mode_t mode);
void rights(mode_t mode);
void time_format(char *time);

#endif
