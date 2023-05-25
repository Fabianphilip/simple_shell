#include "s_shell.h"

/**
 * get_builtin - builtin that pass the command in the arg
 * @cmd: command
 * Return: function pointer of the builtin command
 */
int (*get_builtin(char *cmd))(data_shell *)
{
	builtin_t builtin[] = {
		{ "env", _env },
		{ "exit", exit_shell },
		{ "setenv", _setenv },
		{ "unsetenv", _unsetenv },
		{ "cd", cd_shell },
		{ "help", get_help },
		{ NULL, NULL }
	};
	int f;

	for (f = 0; builtin[f].name; f++)
	{
		if (_strcmp(builtin[f].name, cmd) == 0)
			break;
	}

	return (builtin[f].f);
}
