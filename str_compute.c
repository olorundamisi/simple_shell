#include "hsh.h"


/**
 * _strcat - _stray cat ^._.^ haha
 *
 * @destination: char *
 * @source: char *
 *
 * Return: return value
 */

char *_strcat(char *destination, char *source)
{
	char *ret = destination;

	while (*destination)
		destination++;
	while (*source)
		*destination++ = *source++;
	*destination = *source;
	return (ret);
}


/**
 * _strcmp - compare two strings together
 *
 * @str1: str1
 * @str2: str2
 *
 * Return: you should know this
 *	-ve for str1 < str2, +ve for str1 > str2, zero for str1 == str2
 */

int _strcmp(char *str1, char *str2)
{
	while (*str1 && *str2)
	{
		if (*str1 != *str2)
			return (*str1 - *str2);
		str1++;
		str2++;
	}
	if (*str1 == *str2)
		return (0);
	else
		return (*str1 < *str2 ? -1 : 1);
}


/**
 * _strcpy - _strcpy
 *
 * @destination: char *
 * @source: char *
 *
 * Return: ptr to char * des
 */

char *_strcpy(char *destination, char *source)
{
	int i = 0;

	if (destination == source || source == 0)
		return (destination);
	while (source[i])
	{
		destination[i] = source[i];
		i++;
	}
	destination[i] = 0;
	return (destination);
}


/**
 * _strdup - _strdup
 *
 * @str: char *
 *
 * Return: return value
 */

char *_strdup(const char *str)
{
	int len = 0;
	char *ret;

	if (str == NULL)
		return (NULL);
	while (*str++)
		len++;
	ret = _MEM_ALLOCATE_(sizeof(char) * (len + 1));
	if (!ret)
		return (NULL);
	for (len++; len--;)
		ret[len] = *--str;
	return (ret);
}


/**
 * _strlen - _strlen
 *
 * @s: char *
 *
 * Return: int
 */
int _strlen(char *s)
{
	int i = 0;

	if (!s)
		return (0);

	while (*s++)
		i++;
	return (i);
}
