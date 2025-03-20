#pragma once

// Executes process based on args
// `args[0]` is the process to call
// `args[1:]` are the arguments to the process
// First searches builtins, then programs in `$PATH`
// Returns the status of the process upon execution
int command(char **args);