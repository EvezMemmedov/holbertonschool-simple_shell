#include "main.h"

/**
 * split_line - string-i tokenlərə ayırır
 * @line: istifadəçi input
 * Return: string array
 */
char **split_line(char *line)
{
    int bufsize = 64, i = 0;
    char **tokens = malloc(sizeof(char *) * bufsize);
    char *token;

    if (!tokens)
    {
        perror("allocation error");
        exit(1);
    }

    token = strtok(line, " \t\r\n");
    while (token)
    {
        tokens[i++] = token;

        if (i >= bufsize)
        {
            bufsize += 64;
            tokens = realloc(tokens, sizeof(char *) * bufsize);
            if (!tokens)
            {
                perror("allocation error");
                exit(1);
            }
        }
        token = strtok(NULL, " \t\r\n");
    }
    tokens[i] = NULL;
    return (tokens);
}
