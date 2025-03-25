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
        fgets(buf+wr_off, INPUT_BUF-wr_off, stdin);
        // If there is no newline character in buf, we didn't get all of the input
        // OR stdin reached the EOF
        // Loop through remaining characters in stdin to clear
        // If EOF character is found, exit program (Most likely Ctrl+D was pressed)
        // Otherwise if newline is found, return -1 to specify that there was an error
        if(strchr(buf, '\n') == NULL) {
            char c;
            while(1) {
                c = fgetc(stdin);
                if(c == EOF) exit(1);
                if(c == '\n') return -1;
            }
        }
        // Update write offset to be where end of inputed characters is (exclude newline and null terminator)
        wr_off = strlen(buf)-2;
        // Change newline to null terminator (next character after write offset)
        *(buf+wr_off+1) = '\0'; 

        // Check last entered character in buffer is a pipe
        if(*(buf+wr_off) == '|') {
            // If it is, increment write offset and print pipe prompt descriptor
            wr_off++;
            printf("pipe");

            // Breaks out and prints multiline prompt after
        }
        // Otherwise if last entered character in buffer is NOT a backslash,
        // then we have normal line end and can break
        // Else this will skip and print multiline prompt
        else if(*(buf+wr_off) != '\\') break;

        // Multiline prompt
        printf("> ");
        fflush(stdout);
    }
    // Return length of input (current offset)
    return wr_off+1;
}
