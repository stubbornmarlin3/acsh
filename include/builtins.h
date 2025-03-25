#pragma once

typedef struct BUILTIN{
    char *str;
    int (*func)(char **args, int *io_fd); // io_fd[0] is input fd, io_fd[1] is output fd
} BUILTIN;

#define LEN_BUILTINS 8

extern BUILTIN builtins[LEN_BUILTINS];
extern char **environ;





