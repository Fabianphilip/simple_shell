#include "s_shell.h"

/**
 * parse_arguments - Parse the input string into arguments
 * @input: Input string to parse
 *
 * Return: Array of arguments
 */

char **parse_arguments(char *input)
{
	int i;
	char **arg;
	char *token;

	arg = malloc(sizeof(char *) * (MAX_ARGUMENTS + 1));
	if (arg == NULL)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}

	token = strtok(input, " ");
	i = 0;
	while (token != NULL && i < MAX_ARGUMENTS)
	{
		arg[i] = strdup(token);
		token = strtok(NULL, " ");
		i++;

	}
	arg[i] = NULL;

return (arg);
}
