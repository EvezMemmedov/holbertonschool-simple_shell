#include "main.h"
#include <unistd.h>

/**
 * hsh - simple shell loop
 * Return: 0 on success
 */
int hsh(void)
{
	char *line;
	char **args;
	int status = 1;

	while (status)
	{
		if (isatty(STDIN_FILENO))
			write(STDOUT_FILENO, "$ ", 2);

		line = read_line();
		if (!line)
			return (0);

		args = split_line(line);
		status = execute(args);

		free(line);
		free(args);
	}
	return (0);
}
