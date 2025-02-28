#include "command.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char *get_input() {
    
    // Current buffer size
    // This is init to 1 since the fgets loop will add size COMMAND_BUF to it
    // That way before the alloc call, this will be COMMAND_BUF+1 
    int buf_size = 1;

    // Pointer to input buffer
    // This is init to NULL so that a call to realloc will act like a call to malloc
    input_buf = NULL;

    // Temp pointer for realloc call
    // Also used as the pointer to the newline post-loop
    char *tmp;

    // Write offset for input buffer
    // This is used for when there is more characters than input buffer has room for
    // This is set to negative of COMMAND_BUF so that it will be set to zero before alloc
    int wr_off = -COMMAND_BUF; 

    // Loop through input
    do {
        // Set buffer size
        buf_size += COMMAND_BUF;
        // If buffer size is bigger than the max size, then break
        if(buf_size > COMMAND_BUF_MAX) break;
        // Set write offset
        wr_off += COMMAND_BUF;
        // Allocate memory for input buffer
        if((tmp = (char *)realloc(input_buf, buf_size)) == NULL) {
            perror("alloc");
            exit(1);
        }
        input_buf = tmp;
        // If allocation was okay, get input from stdin
        // Will be placed in input buffer at the write offset
        // Should end with a newline, otherwise subsequent
        // calls will be needed.
        fgets(input_buf+wr_off, COMMAND_BUF+1, stdin);
    } 
    while ((tmp = strchr(input_buf, '\n')) == NULL); // Check if buffer contains a newline, otherwise loop to get more input

    // Change newline to null terminator
    *tmp = '\0';

    // Return pointer to input buffer
    return input_buf;
}

void parse_input() {
    char *token = strtok(input_buf, " ");
    do{
        printf("%s\n", token);
    }
    while ((token = strtok(NULL, " ")) != NULL);
}