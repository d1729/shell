#include <string.h>
#include <stdlib.h>
#include <ctype.h>

char* toLower(char* buf) {
    char* res = (char*) malloc(strlen(buf));

    ssize_t i = 0;
    for(i = 0; buf[i] ; i++) {
        res[i] = tolower(buf[i]);
    }
    res[strlen(res) - 1] = '\0';
    return res;
}
