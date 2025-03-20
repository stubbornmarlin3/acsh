#pragma once

typedef struct BUILTIN{
    char *str;
    int (*func)(char **args);
} BUILTIN;

#define LEN_BUILTINS 4

extern BUILTIN builtins[LEN_BUILTINS];





