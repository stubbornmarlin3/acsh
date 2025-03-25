#include "command.h"
#include "builtins.h"
#include "prompt.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

// Changes directory to the directory in args[1]
// If args[1] is empty, then cd to $HOME
static int acsh_cd(char **args) {
    // If args[1] is empty, cd to $HOME
    if(args[1] == NULL) {
        if(chdir(getenv("HOME")) == 0) return 0;
        perror("chdir");
        exit(1);
    }
    // If args[2] contains something, then there are too many args
    if(args[2] != NULL) {
        fprintf(stderr, "cd: too many arguments\n");
        return 1;
    }
    // Otherwise cd to args[1], checking for chdir errors
    if (chdir(args[1]) == 0) return 0;
    perror("cd");
    return 1;
}

// Print the current working directory
static int acsh_pwd(char **args) {
    // If arguments are given, error because too many args
    if(args[1] != NULL) {
        fprintf(stderr, "pwd: too many arguments\n");
        return 1;
    }
    char buf[PATH_MAX];     // buffer to store cwd
    printf("%s\n", getcwd(buf, sizeof(buf)));   // print to screen
    return 0;
}

// Print args to stdout
static int acsh_echo(char **args) {
    args++; // Increment to get to args[1]
    // Loop through all args and print to screen
    while(*args != NULL) printf("%s ", *(args++));
    // Print newline after all args are printed
    putchar('\n');
    return 0;
}

// Exit acsh with exit code in args[1]
// If args[1] is empty, exit with code 0
static int acsh_exit(char **args) {
    // Too many args check
    if(args[2] != NULL) {
        fprintf(stderr, "exit: too many arguments\n");
        return 1;
    }
    // If args[1] contains value, exit with that value
    if(args[1] != NULL) exit(atoi(args[1]));
    // Else exit 0
    exit(0);
}

// Set environment variables provided in args
// Each arg should be in form name=value
// If no args provided, print all environment variables
static int acsh_export(char **args) {
    // Increment args to get to args[1] and check if empty
    // If it is empty, print all environment variables
    if(*(++args) == NULL) {
        char **var = environ;   // Get variables from external variable environ
        // Loop and print all variables from environ
        while(*var != NULL) printf("%s\n", *(var++));
        return 0;
    }
    // If there is args, add them to environment
    // Loops starting at args[1]
    while(*args != NULL) {
        char *sep; // Will contain address of seperator char
        // Find first '=' to seperate name and value
        // If there is no '=', then create/mark variable
        if((sep = strchr(*args, '=')) == NULL) {
            // Sets variable in args to empty string, without
            // overwriting if it already has a value
            // Check for setenv errors
            if(setenv(*args, "", 0) == -1) {
                perror("export");
                return 1;
            }
        }
        // Else there is a '=', then set variables value
        else {
            *(sep++) = '\0'; // Make '=' seperator into null terminator then increment sep to get start of 'value'
            // Set variable with name in args and value in sep
            // Check for setenv errors
            if(setenv(*args, sep, 1) == -1) {
                perror("export");
                return 1;
            }
        }
        // Increment to get next argument
        args++;
    }
    return 0;
}

static int acsh_unset(char **args) {
    // Increment args to get args[1]
    // If there is no value, then unset does not have enough args
    if(*(++args) == NULL) {
        fprintf(stderr, "unset: not enough arguments\n");
        return 1;
    }
    // Loop from args[1] deleting environment variables with matching name
    while(*args != NULL) {
        // Check for unsetenv errors
        if(unsetenv(*(args++)) == -1) {
            perror("unset");
            return 1;
        }
    }
    return 0;
}



BUILTIN builtins[LEN_BUILTINS] = {
    {"cd", &acsh_cd},
    {"pwd", &acsh_pwd},
    {"echo", &acsh_echo},
    {"exit", &acsh_exit},
    {"export", &acsh_export},
    {"unset", &acsh_unset},
};