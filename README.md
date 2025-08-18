# holbertonschool-simple_shell
# Simple Shell

This project is part of the **Holberton School curriculum**. The goal is to create a simple UNIX command interpreter in C, similar to the `sh` program.

## Features
- Works in **interactive mode**
- Works in **non-interactive mode** (via pipes or reading from a file)
- Executes commands by searching through the `PATH` environment variable
- Implements the `exit` built-in command
- Prints errors in the same format as `sh`
- Uses fundamental system calls and C standard library functions

## Allowed Functions and System Calls
Some of the functions and system calls that can be used in this project include:
- `fork`, `execve`, `wait`, `waitpid`
- `access`, `stat`, `open`, `read`, `write`, `close`
- `malloc`, `free`
- `getline`, `isatty`, `perror`, `printf`
- and string manipulation functions from `string.h`

(See the project requirements for the full list.)

## Compilation
The shell should be compiled with:
```bash
gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o hsh
