#include "parse.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

extern int RETURN_STATUS;

int parse(char *input, char **parsed_args) {
    char c;
    int i = 0;
    int j = 0;
    int n = -1;
    while(1) {
        // Label for breaking out of loop that contains switch
        loop_break:
        // If n is 0, this was an empty token so no need to alloc new memory
        if(n != 0) {
            parsed_args[j] = (char *)malloc(MAX_ARG_SIZE); // Alloc memory for argument
            n = 0;
        }
        while(1) {
            switch (c = input[i++]) // Get character from input
            {
            case '\0':  // Null indicates end of input
                if(n == 0) return j; // If last token was empty
                parsed_args[j++][n] = '\0'; // Make sure to end token with null terminator
                parsed_args[j] = NULL;
                return j; // Return count of args
            case ' ': // Seperate tokens by spaces
                if(n != 0) parsed_args[j++][n] = '\0'; // Make space into null terminator
                goto loop_break; // Break out of loop
            case '"': // Take things in quotes literal
                // Add characters until next quote
                while((c = input[i++]) != '"') {
                    // If end of input before quote, error
                    if(c == '\0') {
                        fprintf(stderr, "acsh: syntax error: missing quote\n");
                        return -1;
                    }
                    parsed_args[j][n++] = c;
                }
                break;
            case '\\': // Escape next character
                // Add next character to arg as is
                parsed_args[j][n++] = input[i++];
                break;
            case '$': // Expand environment variable
                if(input[i] == '?') {
                    i++;
                    n+=snprintf(parsed_args[j]+n, MAX_ARG_SIZE, "%d", RETURN_STATUS);
                }
                else {
                    char *var = &input[i];
                    while((c = input[i++]) != ' ' && c != '\0');
                    input[i-1] = '\0';
                    if((var = getenv(var)) == NULL) break;
                    n+=snprintf(parsed_args[j]+n, MAX_ARG_SIZE, "%s", var);
                }
                break;
            case '|':
                // Check if pipe is first argument OR if last argument was a pipe
                if(j == 0 || strcmp(parsed_args[j-1], "|") == 0) {
                    fprintf(stderr, "acsh: syntax error: unexpected pipe\n");
                    return -1;
                }
                if(n != 0) {
                    parsed_args[j++][n] = '\0'; // End current argument
                    n = 0;
                    parsed_args[j] = (char *)malloc(2); // Alloc memory for new argument (which will just be a single character and null terminator)
                }
                // Set argument to character and null terminator, incrementing j to get ready for next argument
                parsed_args[j][n++] = c;
                parsed_args[j++][n] = '\0';
                goto loop_break; // Break loop since end of argument
            default:
                // Add current character to arg
                parsed_args[j][n++] = c;
                break;
            }
        }
    }
}