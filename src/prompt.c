#include "prompt.h"
#include <unistd.h>
#include <pwd.h>
#include <stdio.h>
#include <stdlib.h>

static uid_t current_uid;              // The current user id
static char username[USERNAME_MAX];    // Current username
static char hostname[HOSTNAME_MAX];    // Current hostname
static char cwd[PATH_MAX];             // Current working directory
extern int RETURN_STATUS;

// Updates the current_uid and username
static void _update_username() {
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
    // Print carriage return first to make sure at beginning of line
    if(getcwd(cwd, sizeof(cwd)) == NULL) exit(1);
    printf("\r[%d]%s@%s:%s %% ", RETURN_STATUS, username, hostname, cwd);
    // Flush stdout stream
    fflush(stdout);
}