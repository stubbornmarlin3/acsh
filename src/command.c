#include "command.h"
#include "builtins.h"
#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int RETURN_STATUS = 0;

// Execute builtins from args
static int execute_builtin(char **args) {
    for(int i=0; i<LEN_BUILTINS; i++) {
        if(strcmp(args[0], builtins[i].str) == 0) {
            return builtins[i].func(args);
        }
    }
    return -1;
}

// Execute process from args
static int execute_proc(char **args) {
    pid_t pid;
    int status;

    pid = fork();
    if(pid == 0) {
        // Child process
        execvp(args[0], args); // Only returns if there is an error
        perror("exec");
        exit(1); // Exit child process if fail to exec
    }
    else if(pid == -1) {
        // Error
        perror("fork");
        return 1;
    }
    else {
        // Parent process
        // Wait for process to exit
        if(waitpid(pid, &status, 0) == -1) {
            perror("waitpid");
            return 1;
        }
        // Check if process exited normally
        if(WIFEXITED(status)) {     // Normal exit
            return WEXITSTATUS(status);
        }
        else if(WIFSIGNALED(status)) {  // Signal exit
            return WTERMSIG(status);
        }
        else {          // Something else
            return status;
        }
    }
}

int command(char **args) {
    if((RETURN_STATUS = execute_builtin(args)) == -1) 
        RETURN_STATUS = execute_proc(args);
    return RETURN_STATUS;
}