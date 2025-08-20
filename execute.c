#include "main.h"
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

/**
 * execute - executes the command
 * @args: array of arguments
 * Return: 1 to continue shell, 0 to exit
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
		if (execve(args[0], args, NULL) == -1)
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
