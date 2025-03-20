#include "prompt.h"
#include "input.h"
#include "parse.h"
#include "command.h"
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>

// Signal handler (just rewrite prompt)
void handler(int sig) {
    printf("\b\b  \n"); // Remove ^C from terminal
    prompt(sig);        // Reprint prompt
}

int main(int argc, char const *argv[])
{  
    // Handle SIGINT user handler to not exit shell
    signal(SIGINT, handler);
    init_prompt();
    char *line = (char *)malloc(INPUT_BUF*sizeof(char));
    char **args = (char **)malloc(MAX_ARGS*sizeof(char *));
    int status = 0;
    int num_args;
    while(1) {
        // Display prompt
        prompt(status);
        // Get input and put in line
        if(input(line) == -1) {
            status = 1;
            continue;
        }
        // Parse input into arguments then execute args
        // Store return status
        if((num_args = parse(line, args)) > 0) status = command(args);
        // Free memory from args
        for(int i=0; i<num_args; i++) {
            free(args[i]);
        }
    }
    // Should never reach this
    return 0;
}

