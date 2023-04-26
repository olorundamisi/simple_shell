#include "hsh.h"


/**
 * is_executable - check if file is executable
 *
 * @shell_args: shell arguments
 * @path: file path
 *
 * Return: read the code
 */

int is_executable(shell_args_t *shell_args, char *path)
{
	struct stat st;

	(void)shell_args;
	if (!path || stat(path, &st))
		return (0);

	if (st.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}


/**
 * duplicate_chars - pretty much what you'd expect
 *
 * @PATH_string: char *
 * @start: integer
 * @stop: integer
 *
 * Return: read the code
 */

char *duplicate_chars(char *PATH_string, int start, int stop)
{
	static char buffer[1024];
	int i = 0, k = 0;

	for (k = 0, i = start; i < stop; i++)
		if (PATH_string[i] != ':')
			buffer[k++] = PATH_string[i];
	buffer[k] = 0;
	return (buffer);
}


/**
 * find_path - check the current PATH_STRING to finid command
 *
 * @shell_args: shell arguments
 * @PATH_string: char *
 * @cmd: char *
 *
 * Return: read the code
 */

char *find_path(shell_args_t *shell_args, char *PATH_string, char *cmd)
{
	int i = 0, current_position = 0;
	char *path;

	if (!PATH_string)
		return (NULL);
	if ((_strlen(cmd) > 2) && _starts_with(cmd, "./"))
	{
		if (is_executable(shell_args, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!PATH_string[i] || PATH_string[i] == ':')
		{
			path = duplicate_chars(PATH_string, current_position, i);
			if (!*path)
				_strcat(path, cmd);
			else
			{
				_strcat(path, "/");
				_strcat(path, cmd);
			}
			if (is_executable(shell_args, path))
				return (path);
			if (!PATH_string[i])
				break;
			current_position = i;
		}
		i++;
	}
	return (NULL);
}


/**
 * lexer - performs lexical analysis and tokenization
 *
 * @str: char *
 * @d: char *
 *
 * Return: ptr to arr of strings or NULL otherwise
 */

char **lexer(char *str, char *d)
{
	int i, j, k, m, word_cnt = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);
	if (!d)
		d = " ";
	for (i = 0; str[i] != '\0'; i++)
		if (!is_delimiter(str[i], d) && (is_delimiter(str[i + 1], d) || !str[i + 1]))
			word_cnt++;

	if (word_cnt == 0)
		return (NULL);
	s = _MEM_ALLOCATE_((1 + word_cnt) * sizeof(char *));
	if (!s)
		return (NULL);
	for (i = 0, j = 0; j < word_cnt; j++)
	{
		while (is_delimiter(str[i], d))
			i++;
		k = 0;
		while (!is_delimiter(str[i + k], d) && str[i + k])
			k++;
		s[j] = _MEM_ALLOCATE_((k + 1) * sizeof(char));
		if (!s[j])
		{
			for (k = 0; k < j; k++)
				free(s[k]);
			free(s);
			return (NULL);
		}
		for (m = 0; m < k; m++)
			s[j][m] = str[i++];
		s[j][m] = 0;
	}
	s[j] = NULL;
	return (s);
}
