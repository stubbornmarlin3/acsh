#pragma once
#include "input.h"

#define MAX_ARGS 255
#define MAX_ARG_SIZE INPUT_BUF // Maximum arg size should be synonumous with the size of the input buffer (cause an arg can only be as big as the the entire buffer)

// Parse input
// Creates tokens from input buffer
// Places args in parsed_args
// Special characters: ",$,\\,|,>,>>,<,&,~
// Returns number of arguments
int parse(char *input, char **parsed_args);