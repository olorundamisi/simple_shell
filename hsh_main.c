#include "hsh.h"


/**
 * start_hsh - helper function for main to start hsh shell
 *
 * @shell_args: shell arguments
 * @arg_vec: argument vector
 *
 * Return: none
 */

void start_hsh(shell_args_t *shell_args, char **arg_vec)
{
	hsh_generate_env(shell_args);
	hsh_r_hist(shell_args);
	hsh_main(shell_args, arg_vec);
}


/**
 * hsh_main - this is the main hsh shell of the program
 *	is consists of the core loop
 *
 * @shell_args: shell arguments
 * @av: argv from main.c main() function
 *
 * Return: 0 for success, 1 or exit_err_code
 */

int hsh_main(shell_args_t *shell_args, char **av)
{
	ssize_t r = 0;
	int bu_ret = 0;

	while (r != -1 && bu_ret != -2)
	{
		clear_shell_args(shell_args);
		/* check if the shell is in interactive mode */
		if ((isatty(STDIN_FILENO) && shell_args->r_file_desc <= 2))
			_insert_str("$ ");
		_error_insert_character(BUF_FLUSH);
		r = r_input(shell_args);
		if (r != -1)
		{
			set_shell_args(shell_args, av);
			bu_ret = get_builtin(shell_args);
			if (bu_ret == -1)
				find_cmd_in_path(shell_args);
		}
		/* check if the shell is in interactive mode */
		else if ((isatty(STDIN_FILENO) && shell_args->r_file_desc <= 2))
			_insert_character('\n');
		free_shell_args(shell_args, 0);
	}
	hsh_w_hist(shell_args);
	free_shell_args(shell_args, 1);
	/* assert that shell is not in interactive mode */
	if (!(isatty(STDIN_FILENO) && shell_args->r_file_desc <= 2) &&
			shell_args->status)
		exit(shell_args->status);
	if (bu_ret == -2)
	{
		if (shell_args->exit_err_code == -1)
			exit(shell_args->status);
		exit(shell_args->exit_err_code);
	}
	return (bu_ret);
}
