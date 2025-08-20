#include "main.h"

/**
 * main - Simple shell loop
 * @argc: argument count (unused)
 * @argv: argument vector (unused)
 *
 * Return: 0 on success
 */
int main(__attribute__((unused)) int argc,
	 __attribute__((unused)) char **argv)
{
	char *line;
	char **args;
	int status = 1;

	while (status)
	{
		write(STDOUT_FILENO, "$ ", 2);

		line = read_line();
		if (!line)
		{
			write(STDOUT_FILENO, "\n", 1);
			break;
		}

		args = split_line(line);
		if (args[0] != NULL)
			status = execute(args);

		free(line);
		free(args);
	}

	return (0);
}
