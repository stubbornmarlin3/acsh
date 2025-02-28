#include "prompt.h"
#include <unistd.h>
#include <pwd.h>
#include <stdio.h>
#include <stdlib.h>


void _update_username() {
    // Get the effective uid of caller
    current_uid = geteuid();
    // Take the uid to get a pointer to passwd struct from <pwd.h> that contains username
    struct passwd *p;
    // Check to make sure pointer is not NULL
    if((p = getpwuid(current_uid)) == NULL) {
        perror("getpwuid");
        exit(1);
    }
    // Store username
    snprintf(username, sizeof(username), "%s", p->pw_name);
}

void init_prompt() {
    // Get and store username
    _update_username();
    // Get and store hostname
    gethostname(hostname, sizeof(hostname));
}

void prompt() {
    // If the user switches (such as from su), update
    if(current_uid != geteuid()) _update_username();

    // Print prompt to stdout
    // Gets the current working directory as well to print
    printf("%s@%s:%s %% ", username, hostname, getcwd(cwd, sizeof(cwd)));
    // Flush stdout stream
    fflush(stdout);
}