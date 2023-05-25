#include "s_shell.h"

/**
 * exit_shell - exits the shell
 *
 * @datash: data relevant (status and args)
 * Return: 0 on success.
 */
int exit_shell(data_shell *datash)
{
	unsigned int ustatus;
	int is_dgt;
	int str_l;
	int b_num;

	if (datash->args[1] != NULL)
	{
		ustatus = _atoi(datash->args[1]);
		is_dgt = _isdigit(datash->args[1]);
		str_l = _strlen(datash->args[1]);
		b_num = ustatus > (unsigned int)INT_MAX;
		if (!is_dgt || str_l > 10 || b_num)
		{
			get_error(datash, 2);
			datash->status = 2;
			return (1);
		}
		datash->status = (ustatus % 256);
	}
	return (0);
}
