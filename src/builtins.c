#include "command.h"
#include "builtins.h"
#include "prompt.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

static int acsh_cd(char **args) {
    if(args[1] == NULL) {
        printf("TODO: CD TO $HOME\n");
        return 2;
    }
    if (chdir(args[1]) == -1) {
        perror("chdir");
        return 1;
    }
    return 0;
}
static int acsh_pwd(char **args) {
    char buf[PATH_MAX];
    printf("%s\n", getcwd(buf, sizeof(buf)));
    return 0;
}
static int acsh_echo(char **args) {
    int i = 1;
    while(args[i] != NULL) {
        printf("%s ", args[i++]);
    }
    putchar('\n');
    return 0;
}
static int acsh_exit(char **args) {
    if(args[1] != NULL) exit(atoi(args[1]));
    exit(0);
    return 0;
}

BUILTIN builtins[LEN_BUILTINS] = {
    {"cd", &acsh_cd},
    {"pwd", &acsh_pwd},
    {"echo", &acsh_echo},
    {"exit", &acsh_exit},
};