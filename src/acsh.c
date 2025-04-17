#include "acsh.h"
#include "prompt.h"
#include "input.h"
#include "parse.h"
#include "command.h"
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <string.h>

const char* VERSION = "acsh 1.0.0-alpha.1";

// Signal handler (just rewrite prompt)
void handler(int sig) {
    putchar('\n');
    prompt();        // Reprint prompt
}

int main(int argc, char const *argv[])
{  
    if(argc > 1) {
        for(int i=1; i<argc; i++) {
            if((strcmp(argv[i], "--version") == 0)) {
                printf("%s\n", VERSION);
                exit(0);
            }
            else{
                fprintf(stderr, "Unknown argument: %s\n", argv[i]);
                exit(1);
            }
        }
    }
    // Handle SIGINT user handler to not exit shell
    signal(SIGINT, handler);
    init_prompt();
    char *line = (char *)malloc(INPUT_BUF);
    char **args = (char **)malloc(MAX_ARGS*sizeof(char *));
    int num_args;
    while(1) {
        // Display prompt
        prompt();
        // Get input and put in line
        if(input(line) == -1) {
            fprintf(stderr, "acsh: input error\n");
            continue;
        };
        // Parse input into arguments then execute args
        // Store return status
        if((num_args = parse(line, args)) > 0) command(args);
        // Free memory from args
        for(int i=0; i<num_args; i++) {
            free(args[i]); // Free memory at pointer
            args[i] = NULL; // NULL out pointer
        }
    }
    // Should never reach this
    return 0;
}

