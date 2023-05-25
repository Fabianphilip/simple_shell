#include "s_shell.h"

/**
 * cmp_env_name - compares env variables names
 * with the name passed.
 * @nenv: name of the environment variable
 * @name: name passed
 *
 * Return: 0 if are not equal. Another value if they are.
 */
int cmp_env_name(const char *nenv, const char *name)
{
	int f;

	for (f = 0; nenv[f] != '='; f++)
	{
		if (nenv[f] != name[f])
		{
			return (0);
		}
	}

	return (f + 1);
}

/**
 * _getenv - get an environment variable
 * @name: name of the environment variable
 * @_environ: environment variable
 *
 * Return: value of the environment variable if is found.
 * In other case, returns NULL.
 */
char *_getenv(const char *name, char **_environ)
{
	char *ptr_env;
	int f, mv;

	/* Initialize ptr_env value */
	ptr_env = NULL;
	mv = 0;
	/* Compare all environment variables */
	/* environ is declared in the header file */
	for (f = 0; _environ[f]; f++)
	{
		/* If name and env are equal */
		mv = cmp_env_name(_environ[f], name);
		if (mv)
		{
			ptr_env = _environ[f];
			break;
		}
	}

	return (ptr_env + mv);
}

/**
 * _env - prints the evironment variables
 *
 * @datash: data relevant.
 * Return: 1 on success.
 */
int _env(data_shell *datash)
{
	int f, t;

	for (f = 0; datash->_environ[f]; f++)
	{

		for (t = 0; datash->_environ[f][t]; t++)
			;

		write(STDOUT_FILENO, datash->_environ[f], t);
		write(STDOUT_FILENO, "\n", 1);
	}
	datash->status = 0;

	return (1);
}
