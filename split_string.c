#include <string.h>
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>

/**
  * split_string - Creates a null terminated array
  * of strings resulting from splitting argv by
  * a delimeter
  * @argv: pointer to string to be split
  * @delim: pointer to string of delimeter
  *
  * Return: pointer to array of split string or
  * NULL in case of failure
  */
char **split_string(char *argv, const char *delim)
{
	char **tokens = NULL;
	int count = 0;
	char *token = NULL;

	tokens = malloc(sizeof(char *));
	if (tokens == NULL)
		return (NULL);
	tokens[0] = NULL;
	token = strtok(argv, delim);
	do {
		if (token != NULL)
		{
			tokens = realloc(tokens, (sizeof(char *) * (++count + 1)));
			if (tokens == NULL)
			{
				return (NULL);
			}
			tokens[count] = NULL;
			tokens[count - 1] = token;
			token = strtok(NULL, delim);
		}
	} while (token != NULL);

	return (tokens);
}
