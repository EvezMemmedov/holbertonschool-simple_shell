#include "main.h"

/**
 * execute - komandani icra edir
 * @args: string array
 *
 * Return: 1 davam etmek üçün, 0 çıxmaq üçün
 */
int execute(char **args)
{
	pid_t pid;
	int status;

	if (strcmp(args[0], "exit") == 0)
		return (0);

	pid = fork();
	if (pid == 0)
	{
		if (execve(args[0], args, NULL) == -1)
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
