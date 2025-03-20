#include "input.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int input(char *buf) {
    
    // Current write offset in buffer
    int wr_off = 0;

    // Input loop
    while(1) {
        
        // Get characters from stdin and place in buffer at offset
        // Only get remaining characters from stdin to fill buffer to prevent overflow
        // If fgets returns 0, Ctrl-D was pressed so exit shell
        if(fgets(buf+wr_off, INPUT_BUF-wr_off, stdin) == 0) {
            puts("exit");
            exit(0);
        }
        // If there is too many characters to place in buffer
        // Or EOF was reached (exit shell)
        // Clear stdin stream and return -1
        if(strchr(buf, '\n') == NULL) {
            if(fgetc(stdin) == EOF) putchar('\r');
            char c;
            while((c = fgetc(stdin)) != '\n' && c != EOF);
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
    *(buf+wr_off+1) = '\0';
    // Return length of input (current offset + 1)
    return wr_off+1;
}
