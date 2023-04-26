#include "hsh.h"


/**
 * is_chain_delimiter - assert if current character is chain_delim
 *
 * @shell_args: the structure encapsulating shell arguments
 * @buffer: char *
 * @p: size_t
 *
 * Return: 1 if is_chain, else 0 if false
 */

int is_chain_delimiter(shell_args_t *shell_args, char *buffer, size_t *p)
{
	size_t j = *p;

	if (buffer[j] == '|' && buffer[j + 1] == '|')
	{
		buffer[j] = 0;
		j++;
		shell_args->buffer_type = CMD_OR;
	}
	else if (buffer[j] == '&' && buffer[j + 1] == '&')
	{
		buffer[j] = 0;
		j++;
		shell_args->buffer_type = CMD_AND;
	}
	else if (buffer[j] == ';')
	{
		buffer[j] = 0;
		shell_args->buffer_type = CMD_CHAIN;
	}
	else
		return (0);
	*p = j;
	return (1);
}


/**
 * assert_cont_chain - assert if continue chaining
 *
 * @shell_args: the structure encapsulating shell arguments
 * @buffer: char *
 * @p: size_t
 * @i: size_t
 * @len: size_t
 *
 * Return: void
 */

void assert_cont_chain(shell_args_t *shell_args, char *buffer, size_t *p,
		size_t i, size_t len)
{
	size_t j = *p;

	if (shell_args->buffer_type == CMD_AND)
	{
		if (shell_args->status)
		{
			buffer[i] = 0;
			j = len;
		}
	}
	if (shell_args->buffer_type == CMD_OR)
	{
		if (!shell_args->status)
		{
			buffer[i] = 0;
			j = len;
		}
	}

	*p = j;
}
