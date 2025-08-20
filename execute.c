#include "main.h"
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern char **environ;

/**
 * get_path - retrieves PATH from environ without getenv
 * Return: pointer to PATH string or NULL
 */
char *get_path(void)
{
	int i = 0;

	while (environ[i])
	{
		if (strncmp(environ[i], "PATH=", 5) == 0)
			return (environ[i] + 5);
		i++;
	}
	return (NULL);
}

/**
 * find_command - searches for command in PATH
 * @cmd: command name
 * Return: full path if found, else NULL
 */
char *find_command(char *cmd)
{
	char *path, *dir, *full_path;
	char *path_copy;
	size_t len;

	if (!cmd)
		return (NULL);

	if (access(cmd, X_OK) == 0)
		return (strdup(cmd));

	path = get_path();
	if (!path)
		return (NULL);

	path_copy = strdup(path);
	if (!path_copy)
		return (NULL);

	dir = strtok(path_copy, ":");
	while (dir)
	{
		len = strlen(dir) + strlen(cmd) + 2;
		full_path = malloc(len);
		if (!full_path)
		{
			free(path_copy);
			return (NULL);
		}
		snprintf(full_path, len, "%s/%s", dir, cmd);
		if (access(full_path, X_OK) == 0)
		{
			free(path_copy);
			return (full_path);
		}
		free(full_path);
		dir = strtok(NULL, ":");
	}
	free(path_copy);
	return (NULL);
}

/**
 * execute - executes command with arguments using PATH
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

		snprintf(error_msg, sizeof(error_msg), "./hsh: 1: %s: not found\n", args[0]);
		write(STDERR_FILENO, error_msg, strlen(error_msg));
		return (127);
	}

	pid = fork();
	if (pid == 0)
	{
		if (execve(cmd_path, args, environ) == -1)
		{
			perror("hsh");
			free(cmd_path);
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

	free(cmd_path);
	return (1);
}
