#include "command.h"
#include <stdio.h>
#include <string.h>

int get_input(char *buf) {
    
    // Current write offset in buffer
    int wr_off = 0;

    // Input loop
    while(1) {
        
        // Get characters from stdin and place in buffer at offset
        // Only get remaining characters from stdin to fill buffer to prevent overflow
        fgets(buf+wr_off, INPUT_BUF-wr_off, stdin);

        // If there is too many characters to place in buffer
        // Clear stdin stream and return -1
        if(strchr(buf, '\n') == NULL) {
            char c;
            while((c = fgetc(stdin)) != '\n');
            return -1;
        }
        // Update write offset to be where end is
        wr_off = strlen(buf)-2;
        // Check if either no input was given (wr_off < 0)
        // OR if the last inputted character was NOT a '\'
        // If so, then break out of loop
        if(wr_off < 0 || *(buf+wr_off) != '\\') break;
        // Otherwise print multiline prompt and loop to get more input
        printf("> ");
        fflush(stdout);
    }
    return wr_off+1;
}

void parse_input(char *input) {
    char *token = strtok(input, " ");
    do{
        printf("%s\n", token);
    }
    while ((token = strtok(NULL, " ")) != NULL);
}