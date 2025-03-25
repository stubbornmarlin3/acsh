#pragma once

typedef struct BUILTIN{
    char *str;
    int (*func)(char **args);
} BUILTIN;

#define LEN_BUILTINS 6

extern BUILTIN builtins[LEN_BUILTINS];
extern char **environ;





