#include "hsh.h"


/**
 * _error_insert_str - puts errors `str`
 *
 * @str: char *
 *
 * Return: void
 */

void _error_insert_str(char *str)
{
	int i = 0;

	if (!str)
		return;
	while (str[i] != '\0')
	{
		_error_insert_character(str[i]);
		i++;
	}
}


/**
 * _error_insert_character - putchar for errors
 *
 * @c: char c
 *
 * Return: 1
 */

int _error_insert_character(char c)
{
	static int i;
	static char buffer[W_BUF_SIZE];

	if (c == BUF_FLUSH || i >= W_BUF_SIZE)
	{
		write(2, buffer, i);
		i = 0;
	}
	if (c != BUF_FLUSH)
		buffer[i++] = c;
	return (1);
}


/**
 * raise_enoent - raise ERROR NO ENTITY
 *	main helper function
 *
 * @arg0: argument 0 - usually ./hsh
 * @arg1: argument 1 - the entity we can't find
 *
 * Return: void
 */

void raise_enoent(char *arg0, char *arg1)
{
	_error_insert_str(arg0);
	_error_insert_str(": 0: Can't open ");
	_error_insert_str(arg1);
	_error_insert_character('\n');
	_error_insert_character(BUF_FLUSH);
}


/**
 * raise_errors - raise ERRORS
 *	main helper functions
 *
 * @arg0: argument 0 - usually ./hsh
 * @arg1: argument 1
 *
 * Return: void
 */

void raise_errors(char *arg0, char *arg1)
{
	if (errno == EACCES)
		exit(126);
	if (errno == ENOENT)
	{
		raise_enoent(arg0, arg1);
		exit(127);
	}
}

