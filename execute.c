#include "main.h"
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

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
char	*find_command(char *cmd)
{
	char	*path, *path_dup, *dir;
	char	*full_path;
	struct stat st;

	if (!cmd)
		return (NULL);

	if (cmd[0] == '/' || cmd[0] == '.')
	{
		if (stat(cmd, &st) == 0)
			return (strdup(cmd));
		return (NULL);
	}

	path = getenv("PATH");
	if (!path || path[0] == '\0')
		return (NULL);

	path_dup = strdup(path);
	if (!path_dup)
		return (NULL);

	dir = strtok(path_dup, ":");
	while (dir)
	{
		full_path = malloc(strlen(dir) + strlen(cmd) + 2);
		if (!full_path)
		{
			free(path_dup);
			return (NULL);
		}
		sprintf(full_path, "%s/%s", dir, cmd);
		if (stat(full_path, &st) == 0)
		{
			free(path_dup);
			return (full_path);
		}
		free(full_path);
		dir = strtok(NULL, ":");
	}

	free(path_dup);
	return (NULL);
}

/**
 * execute - executes a command with arguments
 * @args: array of arguments
 *
 * Return: 1 to continue shell, 0 to exit, 127 if command not found
 */
int execute(char **args)
{
	pid_t	pid;
	int		status;
	char	*cmd_path;

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
