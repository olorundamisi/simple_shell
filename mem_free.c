#include "hsh.h"


/**
 * bfree - free void **
 *	and sets address to NULL
 *
 * @ptr: void **
 *
 * Return: 1 S, else 0
 */

int bfree(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
		return (1);
	}
	return (0);
}


/**
 * ffree - free a char **
 *
 * @pp: char **
 */

void ffree(char **pp)
{
	char **a = pp;

	if (!pp)
		return;
	while (*pp)
		free(*pp++);
	free(a);
}
