#include "hsh.h"


/**
 * _error_atoi - atoi but for errors :)
 *
 * @s: ascii string to convert
 *
 * Return: return 0 if string has no numbers
 *	else return converted numbers or -1 of failure
 */

int _error_atoi(char *s)
{
	unsigned long int res = 0;
	int i = 0;

	if (*s == '+')
		s++;
	for (i = 0;  s[i] != '\0'; i++)
	{
		if (s[i] >= '0' && s[i] <= '9')
		{
			res *= 10;
			res += (s[i] - '0');
			if (res > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (res);
}


/**
 * _error_print_mesg - puts messages on errors
 *
 * @shell_args: shell arguments
 * @err_mesg: char * containing error message
 *
 * Return: void
 */

void _error_print_mesg(shell_args_t *shell_args, char *err_mesg)
{
	_error_insert_str(shell_args->filename);
	_error_insert_str(": ");
	_error_put_dec(shell_args->error_l_cnt, STDERR_FILENO);
	_error_insert_str(": ");
	_error_insert_str(shell_args->argv[0]);
	_error_insert_str(": ");
	_error_insert_str(err_mesg);
}


/**
 * _error_put_dec - put decimal integer usually for errors
 *
 * @input: integer
 * @fd: integer file_desc
 *
 * Return: char_count
 */

int _error_put_dec(int input, int fd)
{
	int (*__insert_character)(char) = _insert_character;
	int i, count = 0;
	unsigned int _abs_, current;

	if (fd == STDERR_FILENO)
		__insert_character = _error_insert_character;
	if (input < 0)
	{
		_abs_ = -input;
		__insert_character('-');
		count++;
	}
	else
		_abs_ = input;
	current = _abs_;
	for (i = 1000000000; i > 1; i /= 10)
	{
		if (_abs_ / i)
		{
			__insert_character('0' + current / i);
			count++;
		}
		current %= i;
	}
	__insert_character('0' + current);
	count++;

	return (count);
}


/**
 * change_num_base - iota i.e. to change number base
 *
 * @num: long integer
 * @base: integer
 * @flags: integer
 *
 * Return: char *
 */

char *change_num_base(long int num, int base, int flags)
{
	static char *array;
	static char buffer[50];
	char sign = 0;
	char *ptr;
	unsigned long n = num;

	if (!(flags & CONVERT_UNSIGNED) && num < 0)
	{
		n = -num;
		sign = '-';

	}
	array = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr = &buffer[49];
	*ptr = '\0';

	do	{
		*--ptr = array[n % base];
		n /= base;
	} while (n != 0);

	if (sign)
		*--ptr = sign;
	return (ptr);
}


/**
 * handle_comments - remove comments from # to NULL
 *
 * @buffer: string address
 *
 * Return: void
 */

void handle_comments(char *buffer)
{
	int i;

	for (i = 0; buffer[i] != '\0'; i++)
		if (buffer[i] == '#' && (!i || buffer[i - 1] == ' '))
		{
			buffer[i] = '\0';
			break;
		}
}
