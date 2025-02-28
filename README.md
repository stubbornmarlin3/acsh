# Aidan's Custom Shell
---
Making a custom shell for my CS456 Honors Project and to eventually be used in **AcOS** (A custom OS that I hope to start making as a personal project)

## Planning
---
The first question I need to ask is what I want my shell to accomplish? In what order will I build functionality?

### Phase 1:
- Display prompt
    - Something like `user@host cwd >>>`
- Read & parse input
    - Tokenize to commands and arguments
    - Should be allowed to accept multiple lines seperated by \
    - Arguments surrounded by "" should not be seperated by spaces
- Execute external programs
    - Use `fork(); exec(); wait();` to execute programs
- Implement basic built-ins
    - Need `cd`, `exit`,`pwd`, and `echo`

### Phase 2:
- Manage environment variables
    - Implement `export` and `unset`
    - Add variable expanision `echo $PATH` -> `echo /bin:/sbin`
- Signal Handling
    - Handle `Ctrl+C` -> `SIGINT`
    - Implement `kill` and `wait`
- Input & Output Direction
    - Implement `<`, `>`, `>>`, and `|`

### Phase 3:
- Implement some more shell builtins
    - `alias`, `unalias`, `.`, `source`, `test`, `return`, `exec`, `eval`, `continue`, `break`
- Shell Scripting Support
