#include "command.h"
#include "builtins.h"
#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

int RETURN_STATUS = 0;

// Execute builtins from args
static int execute_builtin(char **args, int *io_fd) {

    int prev_io_fd[2];
    if((prev_io_fd[0] = dup(STDIN_FILENO)) == -1 || (prev_io_fd[1] = dup(STDOUT_FILENO)) == -1) {
        perror("dup");
        exit(1);
    }
    if(dup2(io_fd[0], STDIN_FILENO) == -1 || dup2(io_fd[1], STDOUT_FILENO) == -1) {
        perror("dup2");
        exit(1);
    }
    
    int status = -1;
    for(int i=0; i<LEN_BUILTINS; i++) {
        if(strcmp(args[0], builtins[i].str) == 0) {
            status = builtins[i].func(args);
            break;
        }
    }
    if(dup2(prev_io_fd[0], STDIN_FILENO) == -1 || dup2(prev_io_fd[1], STDOUT_FILENO) == -1) {
        perror("dup2");
        exit(1);
    }
    close(prev_io_fd[0]);
    close(prev_io_fd[1]);
    return status;
}

// Execute process from args
static int execute_proc(char **args, int *io_fd) {
    pid_t pid;
    int status;

    pid = fork();
    if(pid == 0) {
        // Child process

        // Perform input output redirections
        // io_fd[0] should be where input is coming from
        // io_fd[1] is where output should go to
        // Check for errors
        if(dup2(io_fd[0], STDIN_FILENO) == -1 || dup2(io_fd[1], STDOUT_FILENO) == -1) {
            perror("dup2");
            exit(1);
        }
        // Close file descriptors after using them
        if(io_fd[0] != STDIN_FILENO) close(io_fd[0]);
        if(io_fd[1] != STDOUT_FILENO) close(io_fd[1]);
        
        execvp(args[0], args); // Only returns if there is an error
        if(errno == ENOENT) fprintf(stderr, "acsh: command not found: %s\n", args[0]);
        else perror("exec");
        exit(1); // Exit child process if fail to exec
    }
    else if(pid == -1) {
        // Fork error
        perror("fork");
        exit(1);
    }
    else {
        // Parent process

        // Wait for process to exit
        if(waitpid(pid, &status, 0) == -1) {
            perror("waitpid");
            exit(1);
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

    char **p = args;
    int io_fd[2];
    int read_fd = STDIN_FILENO;
    while(1) {
        if(*p == NULL) {
            if((RETURN_STATUS = execute_builtin(args, (int[]){read_fd, STDOUT_FILENO})) == -1) 
                RETURN_STATUS = execute_proc(args, (int[]){read_fd, STDOUT_FILENO});

            if(read_fd != 0) close(read_fd);
            return RETURN_STATUS;
        }
        else if(strcmp(*p, "|") == 0) {
            *p = NULL;
            if(pipe(io_fd) == -1) {
                perror("pipe");
                exit(1);
            }
            if((RETURN_STATUS = execute_builtin(args, (int[]){read_fd, io_fd[1]})) == -1) 
                RETURN_STATUS = execute_proc(args, (int[]){read_fd, io_fd[1]});

            if(read_fd != 0) close(read_fd);
            close(io_fd[1]);
            read_fd = io_fd[0];
            args = ++p;
        }
        else p++;
    }
}