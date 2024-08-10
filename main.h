#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stddef.h>
#include <ctype.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>

char* toLower(char* buf);
char* get_file_path(char* file_name);
char* get_file_loc(char* path, char* file_path);
int startsWithForwardSlash(const char *str);

#endif
