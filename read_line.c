#include "main.h"

/**
 * read_line - reads a line from stdin
 * Return: pointer to the line read
 */
char *read_line(void)
{
	char *line = NULL;
	size_t bufsize = 0;

	if (isatty(STDIN_FILENO))
		write(1, "$ ", 2);

	if (getline(&line, &bufsize, stdin) == -1)
	{
		free(line);
		return (NULL);
	}

	return (line);
}
