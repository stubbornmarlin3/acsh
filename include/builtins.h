#pragma once

typedef struct BUILTIN{
    char *str;
    int (*func)(char **args);
} BUILTIN;

#define LEN_BUILTINS 4

BUILTIN builtins[LEN_BUILTINS];





