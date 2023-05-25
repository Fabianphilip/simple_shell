#include "s_shell.h"

/**
 * copy_info - copies info to create
 * a new env or alias
 * @name: name (env or alias)
 * @value: value (env or alias)
 *
 * Return: new env or alias.
 */
char *copy_info(char *name, char *value)
{
	char *new;
	int len_name, len_value, len;

	len_name = _strlen(name);
	len_value = _strlen(value);
	len = len_name + l_value + 2;
	new = malloc(sizeof(char) * (l));
	_strcpy(new, name);
	_strcat(new, "=");
	_strcat(new, value);
	_strcat(new, "\0");

	return (new);
}

/**
 * set_env - sets an environment variable
 *
 * @name: name of the environment variable
 * @value: value of the environment variable
 * @datash: data structure (environ)
 * Return: no return
 */
void set_env(char *name, char *value, data_shell *datash)
{
	int f;
	char *var_env, *name_env;

	for (f = 0; datash->_environ[f]; f++)
	{
		var_env = _strdup(datash->_environ[f]);
		name_env = _strtok(var_env, "=");
		if (_strcmp(name_env, name) == 0)
		{
			free(datash->_environ[f]);
			datash->_environ[f] = copy_info(name_env, value);
			free(var_env);
			return;
		}
		free(var_env);
	}

	datash->_environ = _reallocdp(datash->_environ, f, sizeof(char *) * (f + 2));
	datash->_environ[f] = copy_info(name, value);
	datash->_environ[f + 1] = NULL;
}

/**
 * _setenv - compares env variables names
 * with the name passed.
 * @datash: data relevant (env name and env value)
 *
 * Return: 1 on success.
 */
int _setenv(data_shell *datash)
{

	if (datash->args[1] == NULL || datash->args[2] == NULL)
	{
		get_error(datash, -1);
		return (1);
	}

	set_env(datash->args[1], datash->args[2], datash);

	return (1);
}

/**
 * _unsetenv - deletes a environment variable
 *
 * @datash: data relevant (env name)
 *
 * Return: 1 on success.
 */
int _unsetenv(data_shell *datash)
{
	char **realloc_environ;
	char *var_env, *name_env;
	int f, t, d;

	if (datash->args[1] == NULL)
	{
		get_error(datash, -1);
		return (1);
	}
	d = -1;
	for (f = 0; datash->_environ[f]; f++)
	{
		var_env = _strdup(datash->_environ[f]);
		name_env = _strtok(var_env, "=");
		if (_strcmp(name_env, datash->args[1]) == 0)
		{
			d = f;
		}
		free(var_env);
	}
	if (d == -1)
	{
		get_error(datash, -1);
		return (1);
	}
	realloc_environ = malloc(sizeof(char *) * (f));
	for (f = t = 0; datash->_environ[f]; f++)
	{
		if (f != d)
		{
			realloc_environ[t] = datash->_environ[f];
			t++;
		}
	}
	realloc_environ[t] = NULL;
	free(datash->_environ[d]);
	free(datash->_environ);
	datash->_environ = realloc_environ;
	return (1);
}
