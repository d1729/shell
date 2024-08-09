#include "main.h"
#include "helper.h"
#include <ctype.h>
#include <stddef.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    (void) argc, (void) argv;

    char* BUF = NULL;
    size_t count = 0;
    ssize_t char_read = 0;

    pid_t child_pid;
    int status;

    char *token;
    char **array;

    while(1) {
        write(STDOUT_FILENO, "ccsh> ", 6);

        char_read = getline(&BUF, &count, stdin);
        if(char_read == -1) {
            perror("Exiting Shell");
            exit(1);
        }

        if(strcmp(toLower(BUF), "exit") == 0) {
            printf("Goodbye");
            free(BUF);
            exit(1);
        }

        token = strtok(BUF, " \n");
        array = malloc(sizeof(char *) * 1024);
        int i = 0;
        while (token) {
            array[i] = token;
            token = strtok(NULL, " \n");
            i++;
        }
        array[i] = NULL;

        child_pid = fork();
        if(child_pid == -1) {
            perror("Failed to create child process\n");
            exit(41);
        }

        if(child_pid == 0) {
            if(execve(array[0], array, NULL) == -1) {
                perror("Failed to execute");
                exit(97);
            }
        } else {
            wait(&status);
        }

        // token = strtok(BUF, " \n");

        // printf("%s", BUF);
    }
    free(BUF);

    return 0;
}
