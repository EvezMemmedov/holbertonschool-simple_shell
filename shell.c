#include "main.h"

/**
 * hsh - simple shell main loop
 * Return: last status
 */
int hsh(void)
{
	char *line;
	char **args;
	int status = 1, last_status = 0;

	while (status)
	{
		write(STDOUT_FILENO, "$ ", 2);
		line = read_line();
		if (!line)
			break;

		args = split_line(line);
		free(line);

		if (!args)
			continue;

		status = execute(args);
		if (status != 1)
			last_status = status;

		free(args);
	}

	return (last_status);
}
