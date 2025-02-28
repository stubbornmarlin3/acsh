#pragma once

#define COMMAND_BUF 255             // Size to malloc for command buffer
#define COMMAND_BUF_MAX 2048        // Max size to realloc for command buffer

// Prompt input from stdin is read here
char *input_buf;

// Gets input from stdin and returns a pointer
char *get_input(void);
void parse_input(void);