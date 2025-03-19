#pragma once

#define INPUT_BUF 2048  // Size to malloc for input buffer

// Waits for input from command line and places in `buf`
// Must alloc `buf` to size `INPUT_BUF`
// Returns characters read (not including newline or null terminator) on success
// Returns -1 on failure (such as buffer overflow)
int input(char *buf);