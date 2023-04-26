#include "hsh.h"


/**
 * append_to_hist - append entry to history
 *
 * @shell_args: shell arguments
 * @buffer: char *
 * @linecount: history
 *
 * Return: Always 0
 */

int append_to_hist(shell_args_t *shell_args, char *buffer, int linecount)
{
	list_t *node = NULL;

	if (shell_args->history)
		node = shell_args->history;
	append_node_to_end(&node, buffer, linecount);

	if (!shell_args->history)
		shell_args->history = node;
	return (0);
}


/**
 * fetch_hist_file - fetch hist file
 *
 * @shell_args: pass information containing arguments for shell
 *
 * Return: char * containing history file that has been fetched
 */

char *fetch_hist_file(shell_args_t *shell_args)
{
	char *buffer, *dir;

	dir = _getenv(shell_args, "HOME=");
	if (!dir)
		return (NULL);
	buffer = _MEM_ALLOCATE_(sizeof(char) * (_strlen(dir) +
				_strlen(HIST_FILE) + 2));
	if (!buffer)
		return (NULL);
	buffer[0] = 0;
	_strcpy(buffer, dir);
	_strcat(buffer, "/");
	_strcat(buffer, HIST_FILE);
	return (buffer);
}


/**
 * hsh_r_hist - hsh_r_hist
 *
 * @shell_args: pass information pertaining to shell
 *
 * Return: read the code
 */

int hsh_r_hist(shell_args_t *shell_args)
{
	int i, last = 0, linecount = 0;
	ssize_t fd, rdlen, fsize = 0;
	struct stat st;
	char *buffer = NULL, *filename = fetch_hist_file(shell_args);

	if (!filename)
		return (0);

	fd = open(filename, O_RDONLY);
	free(filename);
	if (fd == -1)
		return (0);
	if (!fstat(fd, &st))
		fsize = st.st_size;
	if (fsize < 2)
		return (0);
	buffer = _MEM_ALLOCATE_(sizeof(char) * (fsize + 1));
	if (!buffer)
		return (0);
	rdlen = read(fd, buffer, fsize);
	buffer[fsize] = 0;
	if (rdlen <= 0)
		return (free(buffer), 0);
	close(fd);
	for (i = 0; i < fsize; i++)
		if (buffer[i] == '\n')
		{
			buffer[i] = 0;
			append_to_hist(shell_args, buffer + last, linecount++);
			last = i + 1;
		}
	if (last != i)
		append_to_hist(shell_args, buffer + last, linecount++);
	free(buffer);
	shell_args->hl_count = linecount;
	while (shell_args->hl_count-- >= HIST_MAX)
		del_node_at_idx(&(shell_args->history), 0);
	hsh_renum_hist(shell_args);
	return (shell_args->hl_count);
}


/**
 * hsh_renum_hist - hsh_renum_hist
 *
 * @shell_args: shell arguments
 *
 * Return: read the code
 */

int hsh_renum_hist(shell_args_t *shell_args)
{
	list_t *node = shell_args->history;
	int i = 0;

	while (node)
	{
		node->num = i++;
		node = node->next;
	}
	return (shell_args->hl_count = i);
}


/**
 * hsh_w_hist - write to history file
 *
 * @shell_args: shell arguments
 *
 * Return: read the code
 */

int hsh_w_hist(shell_args_t *shell_args)
{
	ssize_t fd;
	char *filename = fetch_hist_file(shell_args);
	list_t *node = NULL;

	if (!filename)
		return (-1);

	fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);
	if (fd == -1)
		return (-1);
	for (node = shell_args->history; node; node = node->next)
	{
		_insert_str_file_desc(node->str, fd);
		_insert_character_file_desc('\n', fd);
	}
	_insert_character_file_desc(BUF_FLUSH, fd);
	close(fd);
	return (1);
}
