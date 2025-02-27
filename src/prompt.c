#include "prompt.h"
#include <unistd.h>
#include <pwd.h>
#include <stdio.h>
#include <stdlib.h>

void prompt() {
    // Get the real user ID of calling process
    uid_t uid = getuid();
    // Take that ID, and get a pointer to the passwd stucture defined in <pwd.h> that contains the username
    struct passwd *p;
    // Get the pointer and check to make sure it is not NULL
    if ((p = getpwuid(uid)) == NULL) {
        perror("getpwuid");
        exit(1);
    }
    // Create buffer big enough for username and store username from passwd structure 
    char username[USERNAME_MAX];
    snprintf(username, sizeof(username), "%s", p->pw_name);

    // Create buffer big enough for hostname and store
    char hostname[HOSTNAME_MAX];
    gethostname(hostname, sizeof(hostname));

    // Create buffer big enough for cwd and store
    char cwd[PATH_MAX];
    getcwd(cwd, sizeof(cwd));

    // Print prompt and flush stdout stream
    printf("%s@%s %s >>> ", username, hostname, cwd);
    fflush(stdout);
}