#include "hsh.h"


/**
 * _insert_character - _insert_character
 *
 * @c: char
 *
 * Return: int
 */

int _insert_character(char c)
{
	static char buffer[W_BUF_SIZE];
	static int i;

	if (c == BUF_FLUSH || i >= W_BUF_SIZE)
	{
		write(1, buffer, i);
		i = 0;
	}
	if (c != BUF_FLUSH)
		buffer[i++] = c;

	return (1);
}


/**
 * _insert_str - _insert_str in boots :)
 *
 * @str: char * string
 *
 * Return: void
 */

void _insert_str(char *str)
{
	int i = 0;

	if (!str)
		return;
	while (str[i] != '\0')
	{
		_insert_character(str[i]);
		i++;
	}
}


/**
 * _insert_character_file_desc - _insert_character_file_desc
 *
 * @c: char c
 * @fd: integer file descriptor
 *
 * Return: int
 */

int _insert_character_file_desc(char c, int fd)
{
	static int i;
	static char buf[W_BUF_SIZE];

	if (c == BUF_FLUSH || i >= W_BUF_SIZE)
	{
		write(fd, buf, i);
		i = 0;
	}
	if (c != BUF_FLUSH)
		buf[i++] = c;
	return (1);
}


/**
 * _insert_str_file_desc - _insert_str_file_desc
 *
 * @str: char * string
 * @fd: integer file descriptor
 *
 * Return: integer
 */

int _insert_str_file_desc(char *str, int fd)
{
	int i = 0;

	if (!str)
		return (0);
	while (*str)
	{
		i += _insert_character_file_desc(*str++, fd);
	}
	return (i);
}
