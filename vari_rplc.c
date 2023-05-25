#include "s_shell.h"

/**
 * check_env - checks if the typed variable is an env variable
 *
 * @h: head of linked list
 * @in: input string
 * @data: data structure
 * Return: no return
 */
void check_env(r_var **h, char *in, data_shell *data)
{
	int row, chr, f, lval;
	char **_envr;

	_envr = data->_environ;
	for (row = 0; _envr[row]; row++)
	{
		for (f = 1, chr = 0; _envr[row][chr]; chr++)
		{
			if (_envr[row][chr] == '=')
			{
				lval = _strlen(_envr[row] + chr + 1);
				add_rvar_node(h, f, _envr[row] + chr + 1, lval);
				return;
			}

			if (in[f] == _envr[row][chr])
				f++;
			else
				break;
		}
	}

	for (f = 0; in[f]; f++)
	{
		if (in[f] == ' ' || in[f] == '\t' || in[f] == ';' || in[f] == '\n')
			break;
	}

	add_rvar_node(h, f, NULL, 0);
}

/**
 * check_vars - check if the typed variable is $$ or $?
 *
 * @h: head of the linked list
 * @in: input string
 * @st: last status of the Shell
 * @data: data structure
 * Return: no return
 */
int check_vars(r_var **h, char *in, char *st, data_shell *data)
{
	int f, lst, lpd;

	lst = _strlen(st);
	lpd = _strlen(data->pid);

	for (f = 0; in[f]; f++)
	{
		if (in[f] == '$')
		{
			if (in[f + 1] == '?')
				add_rvar_node(h, 2, st, lst), f++;
			else if (in[f + 1] == '$')
				add_rvar_node(h, 2, data->pid, lpd), f++;
			else if (in[f + 1] == '\n')
				add_rvar_node(h, 0, NULL, 0);
			else if (in[f + 1] == '\0')
				add_rvar_node(h, 0, NULL, 0);
			else if (in[f + 1] == ' ')
				add_rvar_node(h, 0, NULL, 0);
			else if (in[f + 1] == '\t')
				add_rvar_node(h, 0, NULL, 0);
			else if (in[f + 1] == ';')
				add_rvar_node(h, 0, NULL, 0);
			else
				check_env(h, in + f, data);
		}
	}

	return (f);
}

/**
 * replaced_input - replaces string into variables
 *
 * @head: head of the linked list
 * @input: input string
 * @new_input: new input string (replaced)
 * @nlen: new length
 * Return: replaced string
 */
char *replaced_input(r_var **head, char *input, char *new_input, int nlen)
{
	r_var *indx;
	int f, t, a;

	indx = *head;
	for (t = f = 0; f < nlen; f++)
	{
		if (input[t] == '$')
		{
			if (!(indx->len_var) && !(indx->len_val))
			{
				new_input[f] = input[t];
				t++;
			}
			else if (indx->len_var && !(indx->len_val))
			{
				for (a = 0; a < indx->len_var; a++)
					t++;
				f--;
			}
			else
			{
				for (a = 0; a < indx->len_val; a++)
				{
					new_input[f] = indx->val[a];
					f++;
				}
				t += (indx->len_var);
				f--;
			}
			indx = indx->next;
		}
		else
		{
			new_input[f] = input[t];
			t++;
		}
	}

	return (new_input);
}

/**
 * rep_var - calls functions to replace string into vars
 *
 * @input: input string
 * @datash: data structure
 * Return: replaced string
 */
char *rep_var(char *input, data_shell *datash)
{
	r_var *head, *indx;
	char *status, *new_input;
	int olen, nlen;

	status = aux_itoa(datash->status);
	head = NULL;

	olen = check_vars(&head, input, status, datash);

	if (head == NULL)
	{
		free(status);
		return (input);
	}

	indx = head;
	nlen = 0;

	while (indx != NULL)
	{
		nlen += (indx->len_val - indx->len_var);
		indx = indx->next;
	}

	nlen += olen;

	new_input = malloc(sizeof(char) * (nlen + 1));
	new_input[nlen] = '\0';

	new_input = replaced_input(&head, input, new_input, nlen);

	free(input);
	free(status);
	free_rvar_list(&head);

	return (new_input);
}
