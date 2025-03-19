#include "prompt.h"
#include "input.h"
#include "parse.h"
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char const *argv[])
{  
    init_prompt();
    char *line = (char *)malloc(INPUT_BUF*sizeof(char));
    char **args = (char **)malloc(MAX_ARGS*sizeof(char *));
    int status = 0;
    while(1) {
        prompt(status);
        if((input(line)) == -1) {
            status = 1;
            continue;
        }
        status = parse(line, args);
        for(int i=0;i<status;i++) {
            printf("%s\n", args[i]);
        }
    }
    free(line);
    free(args);
    return 0;
}
