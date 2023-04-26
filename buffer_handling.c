#include "hsh.h"


/**
 * input_buffer - load commands that are chained to buffer
 *
 * @shell_args: structure encapsulating shell arguments
 * @buffer: char * addr containing buffer
 * @length: addr containing the len variable
 *
 * Return: total number of read bytes
 */

ssize_t input_buffer(shell_args_t *shell_args, char **buffer, size_t *length)
{
	size_t length_p = 0;
	ssize_t ret = 0;

	if (!*length)
	{
		free(*buffer);
		*buffer = NULL;
		signal(SIGINT, _BLOCK_SIGINT);
#if _LIB_GETLINE
		ret = getline(buffer, &length_p, stdin);
#else
		ret = _getline(shell_args, buffer, &length_p);
#endif
		if (ret > 0)
		{
			if ((*buffer)[ret - 1] == '\n')
			{
				(*buffer)[ret - 1] = '\0';
				ret--;
			}
			shell_args->lc_flag = 1;
			handle_comments(*buffer);
			append_to_hist(shell_args, *buffer, shell_args->hl_count++);
			{
				*length = ret;
				shell_args->cmd_buf_addr = buffer;
			}
		}
	}
	return (ret);
}


/**
 * r_input - read input line and strip newline
 *
 * @shell_args: structure encapsulating shell arguments
 *
 * Return: ret - total number of read bytes
 */

ssize_t r_input(shell_args_t *shell_args)
{
	static char *buffer;
	static size_t i, j, len;
	ssize_t ret = 0;
	char **buffer_p = &(shell_args->arg), *p;

	_insert_character(BUF_FLUSH);
	ret = input_buffer(shell_args, &buffer, &len);
	if (ret == -1)
		return (-1);
	if (len)
	{
		j = i;
		p = buffer + i;

		assert_cont_chain(shell_args, buffer, &j, i, len);
		while (j < len)
		{
			if (is_chain_delimiter(shell_args, buffer, &j))
				break;
			j++;
		}

		i = j + 1;
		if (i >= len)
		{
			i = len = 0;
			shell_args->buffer_type = CMD_NORM;
		}

		*buffer_p = p;
		return (_strlen(p));
	}

	*buffer_p = buffer;
	return (ret);
}


/**
 * r_buffer - reads a buffer
 *
 * @shell_args: structure encapsulating shell arguments
 * @buffer: char * addr containing buffer
 * @i: type of size_t
 *
 * Return: ret
 */

ssize_t r_buffer(shell_args_t *shell_args, char *buffer, size_t *i)
{
	ssize_t ret = 0;

	if (*i)
		return (0);
	ret = read(shell_args->r_file_desc, buffer, R_BUF_SIZE);
	if (ret >= 0)
		*i = ret;
	return (ret);
}


/**
 * _getline - read/get the next line of input from standard input
 *
 * @shell_args: structure containining shell arguments
 * @ptr: char **ptr
 * @length: size_t length
 *
 * Return: s
 */

int _getline(shell_args_t *shell_args, char **ptr, size_t *length)
{
	static char buffer[R_BUF_SIZE];
	static size_t i, len;
	size_t k;
	ssize_t r = 0, s = 0;
	char *p = NULL, *new_p = NULL, *c;

	p = *ptr;
	if (p && length)
		s = *length;
	if (i == len)
		i = len = 0;

	r = r_buffer(shell_args, buffer, &len);
	if (r == -1 || (r == 0 && len == 0))
		return (-1);

	c = _strchr(buffer + i, '\n');
	k = c ? 1 + (unsigned int)(c - buffer) : len;
	new_p = _realloc(p, s, s ? s + k : k + 1);
	if (!new_p)
		return (p ? free(p), -1 : -1);

	if (s)
		_strncat(new_p, buffer + i, k - i);
	else
		_strncpy(new_p, buffer + i, k - i + 1);

	s += k - i;
	i = k;
	p = new_p;

	if (length)
		*length = s;
	*ptr = p;
	return (s);
}


/**
 * _BLOCK_SIGINT - BLOCK SIGINT (Ctrl-C)
 *
 * @sig_num: int contains the sig_num
 *
 * Return: void
 */
void _BLOCK_SIGINT(__attribute__((unused))int sig_num)
{
	_insert_str("\n");
	_insert_str("$ ");
	_insert_character(BUF_FLUSH);
}
