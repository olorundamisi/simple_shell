#include "hsh.h"


/**
 * clear_shell_args - clear_shell_args
 *
 * @shell_args: shell arguments
 */

void clear_shell_args(shell_args_t *shell_args)
{
	shell_args->arg = NULL;
	shell_args->argv = NULL;
	shell_args->path = NULL;
	shell_args->argc = 0;
}


/**
 * set_shell_args - set_shell_args
 *
 * @shell_args: shell arguments
 * @argv: argv
 */

void set_shell_args(shell_args_t *shell_args, char **argv)
{
	int i = 0;

	shell_args->filename = argv[0];
	if (shell_args->arg)
	{
		shell_args->argv = lexer(shell_args->arg, " \t");
		if (!shell_args->argv)
		{
			shell_args->argv = _MEM_ALLOCATE_(sizeof(char *) * 2);
			if (shell_args->argv)
			{
				shell_args->argv[0] = _strdup(shell_args->arg);
				shell_args->argv[1] = NULL;
			}
		}
		for (i = 0; shell_args->argv && shell_args->argv[i]; i++)
			;
		shell_args->argc = i;

		_replace_alias(shell_args);
		replace_variables(shell_args);
	}
}


/**
 * free_shell_args - free_shell_args
 *
 * @shell_args: shell arguments
 * @all: integer
 */

void free_shell_args(shell_args_t *shell_args, int all)
{
	ffree(shell_args->argv);
	shell_args->argv = NULL;
	shell_args->path = NULL;
	if (all)
	{
		if (!shell_args->cmd_buf_addr)
			free(shell_args->arg);
		if (shell_args->env)
			clear_llist(&(shell_args->env));
		if (shell_args->history)
			clear_llist(&(shell_args->history));
		if (shell_args->alias)
			clear_llist(&(shell_args->alias));
		ffree(shell_args->environ);
			shell_args->environ = NULL;
		bfree((void **)shell_args->cmd_buf_addr);
		if (shell_args->r_file_desc > 2)
			close(shell_args->r_file_desc);
		_insert_character(BUF_FLUSH);
	}
}
