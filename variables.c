#include "hsh.h"


/**
 * replace_variables - in a lexed/tokenized string, this reps the vars
 *
 * @shell_args: pass information as shell_arg_t
 *
 * Return: 1 S, 0 on failure
 */

int replace_variables(shell_args_t *shell_args)
{
	int i = 0;
	list_t *node;

	for (i = 0; shell_args->argv[i]; i++)
	{
		if (shell_args->argv[i][0] != '$' || !shell_args->argv[i][1])
			continue;

		if (!_strcmp(shell_args->argv[i], "$?"))
		{
			replace_string(&(shell_args->argv[i]),
					_strdup(change_num_base(shell_args->status, 10, 0)));
			continue;
		}
		if (!_strcmp(shell_args->argv[i], "$$"))
		{
			replace_string(&(shell_args->argv[i]),
					_strdup(change_num_base(getpid(), 10, 0)));
			continue;
		}
		node = node_sw(shell_args->env, &shell_args->argv[i][1], '=');
		if (node)
		{
			replace_string(&(shell_args->argv[i]),
					_strdup(_strchr(node->str, '=') + 1));
			continue;
		}
		replace_string(&shell_args->argv[i], _strdup(""));

	}
	return (0);
}


/**
 * replace_string - replaces string
 *
 * @old: char ** old string's address
 * @new: char * new string
 *
 * Return: 1 if replaced, 0 otherwise
 */

int replace_string(char **old, char *new)
{
	free(*old);
	*old = new;
	return (1);
}
