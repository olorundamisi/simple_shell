#include "shell.h"

/**
  * main - Entrypoint to shell interpreter
  * @argc: integer argument count
  * @av: pointer to arrays of string arguments
  * @envp: pointer to array of environmental
  * variables
  * Return: always 0
  */
int main(int argc, char **av, char **envp)
{
	char *paths, **paths_array, *path;
	int status;
	pid_t pid;

	paths = _getenv("PATH", envp);
	paths_array = split_string(paths, ":");
	if (argc > 1) /* run as a command */
	{
		path = search_path(av[1], paths_array);
		if (path !=  NULL)
		{
			pid = fork();
			wait(&status);
			if (pid == 0)
				execve(path, av + 1, envp);
		}
		else
			_printf("%s: 1: %s: not found\n", av[0], av[1]);
	free(path);
	}
	else if (!isatty(STDIN_FILENO))
		non_interractive(av[0], paths_array, envp);
	else
		interractive(av[0], paths_array, envp);

	free(paths);
	free(paths_array);
	return (0);
}
