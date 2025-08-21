#include "main.h"
#include <unistd.h>
#include <stdlib.h>

/**
 * hsh - sadə shell loop
 * Return: 0
 */
int	hsh(void)
{
	char	*line;
	char	**args;
	int	status = 1;

	while (status)
	{
		write(STDOUT_FILENO, "$ ", 2);

		line = read_line();
		if (!line)
		{
			free(line);
			break;
		}

		args = split_line(line);
		if (!args)
		{
			free(line);
			continue;
		}

		status = execute(args);

		free(line);
		free(args);
	}
	return (0);
}
