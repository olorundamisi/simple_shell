#include "hsh.h"


/**
 * _env_emul - my version to emulate the env function
 *	prints the environment we are currently in
 *
 * @shell_args: struct encapsulating arguments
 *
 * Return: 0
 */

int _env_emul(shell_args_t *shell_args)
{
	write_llist_str(shell_args->env);
	return (0);
}


/**
 * _getenv - get/obtain val of environment var
 *
 * @shell_args: shell arguments
 * @name: name of the environment variable
 *
 * Return: the value we're getenv'ing
 */

char *_getenv(shell_args_t *shell_args, const char *name)
{
	list_t *node = shell_args->env;
	char *p;

	while (node)
	{
		p = _starts_with(node->str, name);
		if (p && *p)
			return (p);
		node = node->next;
	}
	return (NULL);
}


/**
 * _setenv_emul - my version to emulate set env,
 *
 * @shell_args: shell arguments
 *
 * Return: 0
 */

int _setenv_emul(shell_args_t *shell_args)
{
	if (shell_args->argc != 3)
	{
		_error_insert_str("Incorrect number of arguments\n");
		return (1);
	}
	if (_setenv(shell_args, shell_args->argv[1], shell_args->argv[2]))
		return (0);
	return (1);
}


/**
 * _unsetenv_emul - my version to emulate unsetenv
 *
 * @shell_args: shell arguments
 *
 * Return: 0
 */

int _unsetenv_emul(shell_args_t *shell_args)
{
	int i;

	if (shell_args->argc == 1)
	{
		_error_insert_str("Too few arguements.\n");
		return (1);
	}
	for (i = 1; i <= shell_args->argc; i++)
		_unsetenv(shell_args, shell_args->argv[i]);

	return (0);
}


/**
 * hsh_generate_env - generate values for env linked list
 *
 * @shell_args: shell arguments
 *
 * Return: 0
 */

int hsh_generate_env(shell_args_t *shell_args)
{
	list_t *node = NULL;
	size_t i;

	for (i = 0; environ[i]; i++)
		append_node_to_end(&node, environ[i], 0);
	shell_args->env = node;
	return (0);
}
