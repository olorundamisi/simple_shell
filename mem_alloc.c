#include "hsh.h"


/**
 * _memset - works like regular memset only much less safe
 *
 * @s: char *
 * @b: char
 * @n: unsigned int
 *
 * Return: ptr to mem area
 */

char *_memset(char *s, char b, unsigned int n)
{
	unsigned int i;

	for (i = 0; i < n; i++)
		s[i] = b;
	return (s);
}


/**
 * _realloc - also work slike regular realloc
 *
 * @ptr: void *
 * @old_size: uint64_t
 * @new_size: uint64_t
 *
 * Return: read the code
 */

void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *p;

	if (!ptr)
		return (_MEM_ALLOCATE_(new_size));
	if (!new_size)
		return (free(ptr), NULL);
	if (new_size == old_size)
		return (ptr);

	p = _MEM_ALLOCATE_(new_size);
	if (!p)
		return (NULL);

	old_size = old_size < new_size ? old_size : new_size;
	while (old_size--)
		p[old_size] = ((char *)ptr)[old_size];
	free(ptr);
	return (p);
}

