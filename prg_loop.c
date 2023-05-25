#include "s_shell.h"

/**
 * without_comment - deletes comments from the input
 *
 * @in: input string
 * Return: input without comments
 */
char *without_comment(char *in)
{
	int f, up;

	up = 0;
	for (f = 0; in[f]; f++)
	{
		if (in[f] == '#')
		{
			if (f == 0)
			{
				free(in);
				return (NULL);
			}

			if (in[f - 1] == ' ' || in[f - 1] == '\t' || in[f - 1] == ';')
				up = f;
		}
	}

	if (up != 0)
	{
		in = _realloc(in, f, up + 1);
		in[up] = '\0';
	}

	return (in);
}

/**
 * shell_loop - Loop of shell
 * @datash: data relevant (av, input, args)
 *
 * Return: no return.
 */
void shell_loop(data_shell *datash)
{
	int lp, i_eof;
	char *input;

	lp = 1;
	while (lp == 1)
	{
		write(STDIN_FILENO, "#FATE ", 6);
		input = read_line(&i_eof);
		if (i_eof != -1)
		{
			input = without_comment(input);
			if (input == NULL)
				continue;

			if (check_syntax_error(datash, input) == 1)
			{
				datash->status = 2;
				free(input);
				continue;
			}
			input = rep_var(input, datash);
			lp = split_commands(datash, input);
			datash->counter += 1;
			free(input);
		}
		else
		{
			lp = 0;
			free(input);
		}
	}
}
