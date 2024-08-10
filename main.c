#include "main.h"
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

    char* path;

    while(1) {
        if(isatty(STDERR_FILENO))
            write(STDOUT_FILENO, "ccsh> ", 6);

        char_read = getline(&BUF, &count, stdin);

        if(char_read == -1) {
            exit(1);
        }

        if(strcmp(toLower(BUF), "exit") == 0) {
            printf("Goodbye\n");
            free(BUF);
            exit(1);
        }

        array = malloc(sizeof(char *) * 1024);
        token = strtok(BUF, " \n");

        int i = 0;
        while (token != NULL) {
            array[i] = token;
            token = strtok(NULL, " \n");
            i++;
        }
        array[i] = NULL;

        path = get_file_path(array[0]);

        child_pid = fork();
        if(child_pid == -1) {
            perror("Failed to create child process\n");
            exit(41);
        }

        if(child_pid == 0) {
            if(execve(path, array, NULL) == -1) {}
        } else {
            wait(&status);
        }
    }
    free(BUF);
    free(path);

    return 0;
}
