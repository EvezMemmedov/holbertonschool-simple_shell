#include "main.h"

/**
 * execute - proqramı işə salır
 * @args: argumentlər array
 * Return: 1 (davam etsin)
 */
int execute(char **args)
{
    pid_t pid;
    int status;

    if (args[0] == NULL)
        return (1);

    pid = fork();
    if (pid == 0)
    {
        if (execvp(args[0], args) == -1)
            perror("hsh");
        exit(EXIT_FAILURE);
    }
    else if (pid < 0)
    {
        perror("hsh");
    }
    else
    {
        waitpid(pid, &status, 0);
    }
    return (1);
}
