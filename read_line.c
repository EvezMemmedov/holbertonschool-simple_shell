#include "main.h"

/**
 * read_line - user-in daxil etdiyi sətri oxuyur
 *
 * Return: string pointer (malloc olunmuş), yoxsa NULL
 */
char *read_line(void)
{
	char *line = NULL;
	size_t bufsize = 0;

	if (getline(&line, &bufsize, stdin) == -1)
	{
		free(line);
		return (NULL);
	}

	return (line);
}
