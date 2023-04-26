#include "shell.h"
/**
  * _strcmp - Compare two strings
  * @s1: pointer to first string
  * @s2: pointer to second string
  *
  * Return: integer negative, zero or positive if
  * s1 is respectively less, equal or greater
  * than s2
  */
int _strcmp(const char *s1, const char *s2)
{
	int index, size1, size2;

	size1 = _strlen(s1);
	size2 = _strlen(s2);

	if (size2 > size1)
		return (size1 - size2);
	else if (size2 < size1)
		return (size1 - size2);

	/* both strings have equal lenghts */
	for (index = 0; index < size1; index++)
	{
		if (s1[index] < s2[index])
			return (-1);
		else if (s1[index] > s2[index])
			return (1);
	}
	return (0);
}
