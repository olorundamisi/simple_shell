#include "hsh.h"


/**
 * _replace_alias - replace aliases in lexed strings
 *
 * @shell_args: passed around information in shell arguments
 *
 * Return: 1 on success or 0
 */

int _replace_alias(shell_args_t *shell_args)
{
	int i;
	list_t *node;
	char *p;

	for (i = 0; i < 10; i++)
	{
		node = node_sw(shell_args->alias, shell_args->argv[0], '=');
		if (!node)
			return (0);
		free(shell_args->argv[0]);
		p = _strchr(node->str, '=');
		if (!p)
			return (0);
		p = _strdup(p + 1);
		if (!p)
			return (0);
		shell_args->argv[0] = p;
	}
	return (1);
}


/**
 * _unset_alias - unset aliases in lexed strings
 *
 * @shell_args: passed around information in shell args
 * @lexed_str: char *lexed_str
 *
 * Return: 0 if successful or 1 otherwise
 */

int _unset_alias(shell_args_t *shell_args, char *lexed_str)
{
	char *p, c;
	int ret;

	p = _strchr(lexed_str, '=');
	if (!p)
		return (1);
	c = *p;
	*p = 0;
	ret = del_node_at_idx(&(shell_args->alias),
		get_node_idx(shell_args->alias, node_sw(shell_args->alias, lexed_str, -1)));
	*p = c;
	return (ret);
}


/**
 * _set_alias - get the aliases in lexed strings
 *
 * @shell_args: passed around information in lexed strings
 * @lexed_str: char * lexed_str
 *
 * Return: 0 if successful or 1 otherwise
 */

int _set_alias(shell_args_t *shell_args, char *lexed_str)
{
	char *p;

	p = _strchr(lexed_str, '=');
	if (!p)
		return (1);
	if (!*++p)
		return (_unset_alias(shell_args, lexed_str));

	_unset_alias(shell_args, lexed_str);
	return (append_node_to_end(&(shell_args->alias), lexed_str, 0) == NULL);
}


/**
 * _print_alias_str - puts and putchars alias char *
 *
 * @node: linked list containing alias node
 *
 * Return: 0 if successful, 1 otherwise
 */

int _print_alias_str(list_t *node)
{
	char *p = NULL, *a = NULL;

	if (node)
	{
		p = _strchr(node->str, '=');
		for (a = node->str; a <= p; a++)
		_insert_character(*a);
		_insert_character('\'');
		_insert_str(p + 1);
		_insert_str("'\n");
		return (0);
	}
	return (1);
}


/**
 * _alias_emul - my emulation of the alias bulitin function in shells
 *
 * @shell_args: shell arguments
 *
 * Return: Always 0
 */

int _alias_emul(shell_args_t *shell_args)
{
	int i = 0;
	char *p = NULL;
	list_t *node = NULL;

	if (shell_args->argc == 1)
	{
		node = shell_args->alias;
		while (node)
		{
			_print_alias_str(node);
			node = node->next;
		}
		return (0);
	}
	for (i = 1; shell_args->argv[i]; i++)
	{
		p = _strchr(shell_args->argv[i], '=');
		if (p)
			_set_alias(shell_args, shell_args->argv[i]);
		else
			_print_alias_str(node_sw(shell_args->alias, shell_args->argv[i], '='));
	}

	return (0);
}
