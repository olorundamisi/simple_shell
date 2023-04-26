#include "shell.h"

/**
  * interractive - run shell in interactive mode
  * @name: pointer to string name of shell
  * @env: pointer to array of environment variable
  * @paths_array: pointer to array of path
  *
  * Return: always 0
  */
int interractive(char *name, char **paths_array, char *env[])
{
	int is_eof = 0, status, P_SIZE = 2;
	pid_t pid;
	input_t *input;
	char *arg_path, **args, prompt[] = "$ ";

	while (1)
	{
		write(STDOUT_FILENO, prompt, P_SIZE);
		for (; !is_eof; free(args), free(arg_path))
		{
			input = get_args_inter();
			if (input == NULL)
				break;
			if (((input->data == NULL) && input->is_eof) || is_exit(input->data))
			{
				if (input->is_eof)
					write(STDOUT_FILENO, "\n", 1);
				free_input(input);
				return (0);
			}
			args = split_string(input->data, " ");
			arg_path = search_path(args[0], paths_array);
			if (arg_path == NULL)
			{
				_printf("%s: 1: %s: not found\n", name,  args[0]);
				is_eof = input->is_eof;
				free_input(input);
				continue;
			}
			pid = fork();
			wait(&status);
			if (pid == 0)
				execve(arg_path, args, env);
			is_eof = input->is_eof;
			free_input(input);
		}
		is_eof = 0;
	}
	return (0);
}

/**
  * non_interractive - run shell in non_interactive mode
  * @name: pointer to string name of shell
  * @env: pointer to array of environment variable
  * @paths_array: pointer to array of path
  *
  * Return: always 0
  */
int non_interractive(char *name, char **paths_array, char *env[])
{
	input_t *input;
	char **args, *arg_path;
	pid_t pid;
	int status;

	while ((input = get_args_non_inter()) != NULL)
	{
		args = split_string(input->data, " ");
		arg_path = search_path(args[0], paths_array);
		if (arg_path == NULL)
		{
			_printf("%s: 1: %s: not found\n", name,  args[0]);
			free(args);
			free_input(input);
			continue;
		}

		pid = fork();
		wait(&status);
		if (pid == 0)
			execve(arg_path, args, env);
		free(args);
		free_input(input);
	}
	return (0);
}
