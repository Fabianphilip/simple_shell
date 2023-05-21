#include "s_shell.h"

/**
 * exec - execute command.
 * @agv: Argument vector.
 * @argument: Argument count.
 */

void exec(char *agv[], char *argument[])
{
	int status;
	pid_t pid;

	pid = fork();
	if (pid == -1)
	{
		exit(EXIT_FAILURE);
	}
	if (pid == 0)
	{
		if (execve(argument[0], argument, NULL) == -1)
		{
			perror(agv[0]);
		}
	}
	else
	{
		wait(&status);
	}
}

/**
 * main - main function.
 * @agc: Argument count.
 * @agv: Argument vector.
 * Return: returns 0.
 */

int main(int agc, char *agv[])
{
	ssize_t value;
	char *s = NULL;
	size_t n = 0;
	char *argument[] = {NULL, NULL};
	int f;

	(void)agc;
	while (1)
	{
		if (isatty(STDIN_FILENO))
			write(STDOUT_FILENO, "My_shell# ", 10);

		s = malloc(sizeof(char) * n);
		if (s == NULL)
		{
			exit(EXIT_FAILURE);
		}
		value = getline(&s, &n, stdin);
		if (value == -1)
		{
			free(s);
			exit(EXIT_SUCCESS);
		}
		f = 0;
		while (s[f])
		{
			if (s[f] == '\n')
			{
				s[f] = 0;
			}
			f++;
		}
		argument[0] = s;
		exec(agv, argument);

		free(s);
	}
	return (0);
}
