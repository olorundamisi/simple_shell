#include "hsh.h"


/**
 * _strncpy - _strncpy
 *
 * @destination: char *
 * @source: char *
 * @n: int
 *
 * Return: read the code
 */

char *_strncpy(char *destination, char *source, int n)
{
	int i, j;
	char *s = destination;

	i = 0;
	while (source[i] != '\0' && i < n - 1)
	{
		destination[i] = source[i];
		i++;
	}
	if (i < n)
	{
		j = i;
		while (j < n)
		{
			destination[j] = '\0';
			j++;
		}
	}
	return (s);
}


/**
 * _strncat - _strncat
 *
 * @destination: char *
 * @source: tchar *
 * @n: integer
 *
 * Return: read the code
 */

char *_strncat(char *destination, char *source, int n)
{
	int i, j;
	char *s = destination;

	i = 0;
	j = 0;
	while (destination[i] != '\0')
		i++;
	while (source[j] != '\0' && j < n)
	{
		destination[i] = source[j];
		i++;
		j++;
	}
	if (j < n)
		destination[i] = '\0';
	return (s);
}


/**
 * *_strchr - _strchr
 *
 * @s: char *
 * @c: char
 *
 * Return: read the code
 */

char *_strchr(char *s, char c)
{
	do {
		if (*s == c)
			return (s);
	} while (*s++ != '\0');

	return (NULL);
}
