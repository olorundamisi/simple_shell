#include "hsh.h"


/**
 * _starts_with - assert if source starts with str
 *
 * @source: string to search in
 * @str: substring to look for
 *
 * Return: addr to next character in source string
 */

char *_starts_with(const char *source, const char *str)
{
	while (*str)
		if (*str++ != *source++)
			return (NULL);
	return ((char *)source);
}


/**
 * _get_environ - return a char * copy of environ
 *
 * @shell_args: arguments for shell
 *
 * Return: 0
 */

char **_get_environ(shell_args_t *shell_args)
{
	if (!shell_args->environ || shell_args->changed_environ)
	{
		shell_args->environ = list_to_strings(shell_args->env);
		shell_args->changed_environ = 0;
	}

	return (shell_args->environ);
}


/**
 * _unsetenv - unset envir var
 *
 * @shell_args: arguments of shell
 * @var: string var
 *
 * Return: 1 if deleted, else 0
 */

int _unsetenv(shell_args_t *shell_args, char *var)
{
	list_t *node = shell_args->env;
	size_t i = 0;
	char *p;

	if (!node || !var)
		return (0);

	while (node)
	{
		p = _starts_with(node->str, var);
		if (p && *p == '=')
		{
			shell_args->changed_environ = del_node_at_idx(&(shell_args->env), i);
			i = 0;
			node = shell_args->env;
			continue;
		}
		node = node->next;
		i++;
	}
	return (shell_args->changed_environ);
}


/**
 * _setenv - init or set a new envir var, also mod existing one
 *
 * @shell_args: shell arguments
 * @var: string var
 * @value: sting value
 *
 * Return: 0
 */

int _setenv(shell_args_t *shell_args, char *var, char *value)
{
	char *buffer = NULL;
	list_t *node;
	char *p;

	if (!var || !value)
		return (0);

	buffer = _MEM_ALLOCATE_(_strlen(var) + _strlen(value) + 2);
	if (!buffer)
		return (1);
	_strcpy(buffer, var);
	_strcat(buffer, "=");
	_strcat(buffer, value);
	node = shell_args->env;
	while (node)
	{
		p = _starts_with(node->str, var);
		if (p && *p == '=')
		{
			free(node->str);
			node->str = buffer;
			shell_args->changed_environ = 1;
			return (0);
		}
		node = node->next;
	}
	append_node_to_end(&(shell_args->env), buffer, 0);
	free(buffer);
	shell_args->changed_environ = 1;
	return (0);
}

