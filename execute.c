#include "main.h"
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <stdio.h>

/**
 * find_command - finds command in /bin and /usr/bin manually
 * @cmd: command
 * Return: full path if exists, else NULL
 */
char *find_command(char *cmd)
{
	char *paths[] = {"/bin/", "/usr/bin/", NULL};
	char *full_path;
	int i;
	struct stat st;

	if (!cmd)
		return (NULL);

	if (cmd[0] == '/' || cmd[0] == '.')
	{
		if (stat(cmd, &st) == 0)
			return (strdup(cmd));
		return (NULL);
	}

	for (i = 0; paths[i]; i++)
	{
		full_path = malloc(strlen(paths[i]) + strlen(cmd) + 1);
		if (!full_path)
			return (NULL);
		strcpy(full_path, paths[i]);
		strcat(full_path, cmd);

		if (stat(full_path, &st) == 0)
			return (full_path);

		free(full_path);
	}

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
		return (-1);

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
