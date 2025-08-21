#include "main.h"
#include <stdlib.h>
#include <unistd.h>

/**
 * read_line - istifadəçidən sətir oxuyur
 * Return: oxunan sətir
 */
char	*read_line(void)
{
	char	*buffer = NULL;
	size_t	bufsize = 0;
	ssize_t	nread;

	nread = getline(&buffer, &bufsize, stdin);
	if (nread == -1)
	{
		free(buffer);
		return (NULL);
	}
	if (buffer[nread - 1] == '\n')
		buffer[nread - 1] = '\0';
	return (buffer);
}

