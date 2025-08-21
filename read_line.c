#include "main.h"

/**
 * read_line - oxuyur inputdan
 * Return: string (line)
 */
char *read_line(void)
{
    char *line = NULL;
    size_t bufsize = 0;

    if (getline(&line, &bufsize, stdin) == -1)
    {
        if (feof(stdin))
        {
            free(line);
            exit(0);
        }
        else
        {
            perror("read_line");
            exit(1);
        }
    }
    return (line);
}
