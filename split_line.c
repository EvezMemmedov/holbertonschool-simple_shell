#include "main.h"

/**
 * split_line - inputu bosluqlara göe parçalayr
 * @line: daxil edilen string
 *
 * Return: pointer to array of strings
 */
char **split_line(char *line)
{
	char *token;
	char **tokens;
	int bufsize = 64, i = 0;

	tokens = malloc(sizeof(char *) * bufsize);
	if (!tokens)
	{
		perror("hsh");
		exit(EXIT_FAILURE);
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
				perror("hsh");
				exit(EXIT_FAILURE);
			}
		}
		token = strtok(NULL, " \t\r\n");
	}
	tokens[i] = NULL;
	return (tokens);
}

