#include "main.h"

/**
 * hsh - simple shell
 * Return: 0
 */
int hsh(void)
{
	char *line;
	char **args;
	int status = 1;

	while (1)
	{
		line = read_line();
		if (!line)
			break;

		args = split_line(line);
		if (args[0] != NULL)
			status = execute(args);

		free(line);
		free(args);
	}

	return (status);
}
