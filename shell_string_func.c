#include "shell.h"

/**
  * _strlen - Find the length of given string
  * @s: pointer to string
  *
  * Return: integer lenght of string
  */
int _strlen(const char *s)
{
	int len;

	if (s == NULL)
		return (0);

	for (len = 0; s[len] != '\0'; len++)
		;
	return (len);
}

/**
  * concat - A variadic function that concatenates a
  * given number of strings
  * @ac: unsigned integer number of strings
  * Return: pointer to string
  */
char *concat(size_t ac, ...)
{
	va_list arg;
	char buff[1024], *next;
	int num, index, len, count;

	init_array(buff, 1024);
	va_start(arg, ac);
	num = 0;
	for (count = 0; count < ac; count++)
	{
		next = va_arg(arg, char *);
		len = _strlen(next);
		index = 0;
		for (; index < len; index++, num++)
			buff[num] = next[index];
	}
	va_end(arg);

	return (_strndup(buff, num));
}

/**
  * _strndup - Create new copy of string s with at
  * most n copies of s
  * @s: string to make copy of
  * @n: integer number of character in s to make a
  * new string
  *
  * Return: pointer to string on success else NULL
  */
char *_strndup(const char *s, int n)
{
	int len, index;
	char *new = NULL;

	len = _strlen(s);
	new = malloc(n + 1);
	if (new == NULL)
		return (NULL);

	for (index = 0; index < n; index++)
		new[index] = s[index];
	new[index] = '\0';
	return (new);
}


/**
  * _strdup - Create new copy of string s
 * @s: string to make copy of
  *
  * Return: pointer to string on success else NULL
  */
char *_strdup(const char *s)
{
	int len, index;
	char *new = NULL;

	len = _strlen(s);
	new =  malloc(len + 1);
	if (new == NULL)
		return (NULL);

	for (index = 0; index < len; index++)
		new[index] = s[index];
	new[index] = '\0';

	return (new);
}

/**
  * init_array - Set all characters in a string to
  * null '\0'
  * @buff: pointer to string
  * @num: integer number of items to set to null
  * Return: void
  */
void init_array(char *buff, size_t num)
{
	size_t index = 0;

	while ((buff != NULL) && (index < num))
	{
		buff[index] = '\0';
		index++;
	}
}
