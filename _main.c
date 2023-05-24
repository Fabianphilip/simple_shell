#include "s_shell.h"

/**
 * run - run command
 * @ac: argument passed to the program
 * @av: argument vector
 * @buffer: contains string from getline
 */

void run(char **ac, char **av, char *buffer)
{
	int wstatus;
	pid_t pid;

	pid = fork();
	if (pid == -1)
	{
		perror(av[0]);
		exit(EXIT_FAILURE);
	}
	if (pid == 0)
	{
		if (execve(ac[0], ac, NULL) == -1)
		{
			perror(av[0]);
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		wait(&wstatus);
	}
	free(buffer);
}
/**
 * main - Entry point
 * @argc: argument count
 * @argv: argument vector
 * Return: always 0(success)
 */
int main(int argc, char *argv[])
{
	char *ac[] = {NULL, NULL}, *buffer = NULL;
	int f;
	size_t n = 0;
	ssize_t line;

	(void)argc;
	while (1)
	{
		if (isatty(STDIN_FILENO))
			write(STDOUT_FILENO, "C_is_fun$ ", 10);

		buffer = malloc(sizeof(char) * n);
		if (buffer == NULL)
		{
			perror(argv[0]);
			exit(EXIT_FAILURE);
		}
		line = getline(&buffer, &n, stdin);
		if (line == -1)
		{
			free(buffer);
			exit(EXIT_FAILURE);
		}
		if (line == 0)
		{
			free(buffer);
			exit(EXIT_SUCCESS);
		}
		for (f = 0; buffer[f]; f++)
		{
			if (buffer[f] == '\n')
				buffer[f] = 0;
		}
		ac[0] = buffer;
		run(ac, argv, buffer);
	}
	free(buffer);
	return (0);
}
