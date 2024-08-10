#include "main.h"

char* toLower(char* buf) {
    char* res = (char*) malloc(strlen(buf));

    ssize_t i = 0;
    for(i = 0; buf[i] ; i++) {
        res[i] = tolower(buf[i]);
    }
    res[strlen(res) - 1] = '\0';
    return res;
}


int startsWithForwardSlash(const char* str) {
    if(str != NULL || str[0] == '/') {
        return 1;
    }

    return 0;
}

char* get_file_loc(char* path, char* file_name) {
    char *path_copy, *token;
    char* path_buffer = NULL;
    struct stat file_path;

    path_copy = strdup(path);
    token = strtok(path_copy, ":");

    while (token) {
        if(path_buffer) {
            free(path_buffer);
            path_buffer = NULL;
        }

        path_buffer = malloc(strlen(token) + strlen(file_name) + 2);
        if(!path_buffer) {
            perror("Error: malloc failed");
            exit(EXIT_FAILURE);
        }
        strcpy(path_buffer, token);
        strcat(path_buffer, "/");
        strcat(path_buffer, file_name);
        strcat(path_buffer, "\0");

        if(access(path_buffer, X_OK) == 0 && stat(path_buffer, &file_path) == 0) {
           free(path_copy);
           return path_buffer;
        }

        token = strtok(NULL, ":");
    }
    free(path_copy);
    if(path_buffer){
        free(path_buffer);
    }
    return NULL;
}

char* get_file_path(char* file_name) {
    if((startsWithForwardSlash(file_name) == 1) && (access(file_name, X_OK) == 0))
        return strdup(file_name);

    char *path = getenv("PATH");
    if(!path) {
        return NULL;
    }

    char* full_path;
    full_path = get_file_loc(path, file_name);

    if(full_path == NULL) {
        write(2, file_name, strlen(file_name));
        write(2, ": command not found\n", 21);
        return NULL;
    }

    return full_path;
}
