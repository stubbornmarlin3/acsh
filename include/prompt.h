#pragma once

#include <unistd.h>

#define HOSTNAME_MAX 256 // POSIX defines the max hostname is 255 character NOT including the NULL character, so add 1 for NULL byte
#define USERNAME_MAX 256 // Longest username (POSIX says this is 9, Linux says this is 32, and MacOS says 255 so I am taking the biggest) Adding 1 to include NULL byte

#define PATH_MAX 4096 // Longest path length (POSIX says this is 4096 due to modern filesystems)

uid_t current_uid;              // The current user id
char username[USERNAME_MAX];    // Current username
char hostname[HOSTNAME_MAX];    // Current hostname
char cwd[PATH_MAX];             // Current working directory

// Updates the current_uid and username
void _update_username(void);

// Initialize the prompt with current username and hostname
void init_prompt(void);

// Print prompt `user@host cwd >>>`
void prompt(void);  // TODO: Add support for custom prompts