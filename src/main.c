#include "prompt.h"
#include "command.h"

int main(int argc, char const *argv[])
{   
    init_prompt();
    while(1) {
        prompt();
        get_input();
        parse_input();
    }
    return 0;
}
