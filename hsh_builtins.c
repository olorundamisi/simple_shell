#include "hsh.h"


/**
 * get_builtin - get the desired builtin we're looking for
 *	uses a dictionary
 *
 * @shell_args: shell arguments
 *
 * Return: Abeg read the code
 */

int get_builtin(shell_args_t *shell_args)
{
	int i, built_in_ret = -1;
	builtin_dict builtin_dct[] = {
		{"exit", _exit_emul},
		{"env", _env_emul},
		{"help", _help_emul},
		{"history", _history_emul},
		{"setenv", _setenv_emul},
		{"unsetenv", _unsetenv_emul},
		{"cd", _cd_emul},
		{"alias", _alias_emul},
		{NULL, NULL}
	};

	for (i = 0; builtin_dct[i].type; i++)
		if (_strcmp(shell_args->argv[0], builtin_dct[i].type) == 0)
		{
			shell_args->error_l_cnt++;
			built_in_ret = builtin_dct[i].func(shell_args);
			break;
		}
	return (built_in_ret);
}


/**
 * _cd_emul - my emulation of cd
 *
 * @shell_args: shell arguments
 *
 * Return: 0
 */

int _cd_emul(shell_args_t *shell_args)
{
	char *s, *dir, buffer[1024];
	int chdir_ret;

	s = getcwd(buffer, 1024);
	if (!s)
		_insert_str("todo: >>getcwd failure emsg here<<\n");
	if (!shell_args->argv[1])
	{
		dir = _getenv(shell_args, "home=");
		if (!dir)
			chdir_ret = /* todo: what should this be? */
				chdir((dir = _getenv(shell_args, "pwd=")) ? dir : "/");
		else
			chdir_ret = chdir(dir);
	}
	else if (_strcmp(shell_args->argv[1], "-") == 0)
	{
		if (!_getenv(shell_args, "oldpwd="))
		{
			_insert_str(s);
			_insert_character('\n');
			return (1);
		}
		_insert_str(_getenv(shell_args, "oldpwd=")), _insert_character('\n');
		chdir_ret = /* todo: what should this be? */
			chdir((dir = _getenv(shell_args, "oldpwd=")) ? dir : "/");
	}
	else
		chdir_ret = chdir(shell_args->argv[1]);
	if (chdir_ret == -1)
	{
		_error_print_mesg(shell_args, "can't cd to ");
		_error_insert_str(shell_args->argv[1]), _error_insert_character('\n');
	}
	else
	{
		_setenv(shell_args, "oldpwd", _getenv(shell_args, "pwd="));
		_setenv(shell_args, "pwd", getcwd(buffer, 1024));
	}
	return (0);
}


/**
 * _exit_emul - my emulation of exit shell
 *
 * @shell_args: shell arguments
 *
 * Return: read the code
 */

int _exit_emul(shell_args_t *shell_args)
{
	int exitcheck;

	if (shell_args->argv[1])
	{
		exitcheck = _error_atoi(shell_args->argv[1]);
		if (exitcheck == -1)
		{
			shell_args->status = 2;
			_error_print_mesg(shell_args, "illegal number: ");
			_error_insert_str(shell_args->argv[1]);
			_error_insert_character('\n');
			return (1);
		}
		shell_args->exit_err_code = _error_atoi(shell_args->argv[1]);
		return (-2);
	}
	shell_args->exit_err_code = -1;
	return (-2);
}


/**
 * _help_emul - emulation of help
 *
 * @shell_args: shell arguments
 *
 * Return: 0
 */

int _help_emul(shell_args_t *shell_args)
{
	char **arg_arr;

	arg_arr = shell_args->argv;
	_insert_str("help call works. function not yet implemented \n");
	if (0)
		_insert_str(*arg_arr);
	return (0);
}


/**
 * _history_emul - emulation of history
 *
 * @shell_args: shell arguments
 *
 * Return: 0
 */

int _history_emul(shell_args_t *shell_args)
{
	write_llist(shell_args->history);
	return (0);
}
