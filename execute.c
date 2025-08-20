#include "main.h"
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern char **environ;

/**
 * execute - executes the command with arguments
 * @args: array of arguments
 * Return: 1 to continue, 0 to exit
 */
int	execute(char **args)
{
	pid_t	pid;
	int		status;

	if (strcmp(args[0], "exit") == 0)
		return (0);

	pid = fork();
	if (pid == 0)
	{
		if (execve(args[0], args, environ) == -1)
		{
			perror("hsh");
			exit(EXIT_FAILURE);
		}
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
