#include "hsh.h"


/**
 * hsh_asm_file_desc - checks if character is a delimeter
 *
 * @file_desc: the char to check
 *
 * Return: void
 */

void hsh_asm_file_desc(int file_desc)
{
	asm ("mov %1, %0\n\tadd $3, %0" : "=r" (file_desc) : "r" (file_desc));
}


/**
 * is_delimiter - assert if the current character is a delimiter
 *
 * @c: char
 * @delimiter: char delim
 *
 * Return: 1 T, 0 F
 */

int is_delimiter(char c, char *delimiter)
{
	while (*delimiter)
		if (*delimiter++ == c)
			return (1);
	return (0);
}


/**
 * find_cmd_in_path - look for command in path
 *
 * @shell_args: shell arguments
 *
 * Return: void
 */

void find_cmd_in_path(shell_args_t *shell_args)
{
	char *path = NULL;
	int i, k;

	shell_args->path = shell_args->argv[0];
	if (shell_args->lc_flag == 1)
	{
		shell_args->error_l_cnt++;
		shell_args->lc_flag = 0;
	}
	for (i = 0, k = 0; shell_args->arg[i]; i++)
		if (!is_delimiter(shell_args->arg[i], " \t\n"))
			k++;
	if (!k)
		return;

	path = find_path(shell_args, _getenv(shell_args, "PATH="),
			shell_args->argv[0]);
	if (path)
	{
		shell_args->path = path;
		fork_exec_thread(shell_args);
	}
	else
	{
		if (((isatty(STDIN_FILENO) && shell_args->r_file_desc <= 2)
					|| _getenv(shell_args, "PATH=")
					|| shell_args->argv[0][0] == '/')
				&& is_executable(shell_args, shell_args->argv[0]))
			fork_exec_thread(shell_args);
		else if (*(shell_args->arg) != '\n')
		{
			shell_args->status = 127;
			_error_print_mesg(shell_args, "not found\n");
		}
	}
}


/**
 * fork_exec_thread - run a command by forking an exec thread
 *
 * @shell_args: shell arguments
 *
 * Return: void
 */

void fork_exec_thread(shell_args_t *shell_args)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(shell_args->path, shell_args->argv,
					_get_environ(shell_args)) == -1)
		{
			free_shell_args(shell_args, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
	}
	else
	{
		wait(&(shell_args->status));
		if (WIFEXITED(shell_args->status))
		{
			shell_args->status = WEXITSTATUS(shell_args->status);
			if (shell_args->status == 126)
				_error_print_mesg(shell_args, "Permission denied\n");
		}
	}
}
