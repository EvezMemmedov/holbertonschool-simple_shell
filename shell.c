#include "main.h"

/**
 * main - sadə shell
 * Return: 0
 */
int main(void)
{
    char *line;
    char **args;
    int status = 1;

    while (status)
    {
        write(STDOUT_FILENO, "$ ", 2);
        line = read_line();
        args = split_line(line);
        status = execute(args);

        free(line);
        free(args);
    }
    return (0);
}
