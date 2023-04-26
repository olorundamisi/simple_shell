#include "shell.h"

/**
  * _getenv - Finds the value of an env variable
  * @key: pointer to string env variable name
  * @environ: pointer to array of env variables
  *
  * Return: pointer to string or NULL on failure
  */
char *_getenv(const char *key, char *environ[])
{
	char *value, *env;
	int key_len;
	int index, idx;

	if (key == NULL || environ == NULL)
		return (NULL);
	key_len = _strlen(key);

	index = 0;
	env = environ[index];
	while (env != NULL)
	{
		idx = 0;
		while (idx < key_len)
		{
			if (key[idx] != env[idx])
				break;
			idx++;
		}
		if (idx == key_len && env[idx] == '=')
			return (_strdup(env + idx + 1));
		index++;
		env = environ[index];
	}
	return (NULL);
}
