#include "prompt.h"
#include "command.h"
#include <stdlib.h>

int main(int argc, char const *argv[])
{  
    init_prompt();
    char *line = (char *)malloc(INPUT_BUF);
    int status = 0;
    while(1) {
        prompt(status);
        if((get_input(line)) == -1) {
            status = 1;
            continue;
        }
        parse_input(line);
        status = 0;
    }
    free(line);
    return 0;
}
