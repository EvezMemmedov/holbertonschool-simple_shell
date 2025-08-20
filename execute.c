#include "main.h"
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <stdio.h>

/**
 * find_command - finds command without getenv
 * @cmd: command
 * Return: full path if exists, else NULL
 */
char *find_command(char *cmd)
{
	struct stat st;

	if (!cmd)
		return (NULL);

	/* tam yol verilmişsə və fayl mövcuddursa */
	if (cmd[0] == '/' || cmd[0] == '.')
	{
		if (stat(cmd, &st) == 0)
			return (strdup(cmd));
		return (NULL);
	}

	/* PATH yoxlamadan NULL qaytar */
	return (NULL);
}

/**
 * execute - executes the command with arguments
 * @args: array of arguments
 * Return: 1 to continue, 0 to exit
 */
int execute(char **args)
{
	pid_t pid;
	int status;
	char *cmd_path;

	if (!args || !args[0])
		return (1);

	if (strcmp(args[0], "exit") == 0)
		return (0);

	cmd_path = find_command(args[0]);
	if (!cmd_path)
	{
		char error_msg[100];

		snprintf(error_msg, sizeof(error_msg),
			 "./hsh: 1: %s: not found\n", args[0]);
		write(STDERR_FILENO, error_msg, strlen(error_msg));
		return (127);
	}

	pid = fork();
	if (pid == 0)
	{
		if (execve(cmd_path, args, NULL) == -1)
		{
			perror("hsh");
			free(cmd_path);
			exit(EXIT_FAILURE);
		}
	}
	else if (pid < 0)
	{
		perror("hsh");
		free(cmd_path);
		return (1);
	}
	else
		waitpid(pid, &status, 0);

	free(cmd_path);

	if (WIFEXITED(status))
		return (WEXITSTATUS(status));

	return (1);
}
