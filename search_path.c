#include "shell.h"
/**
  * search_path - search for given path in array of
  * paths
  * @path: pointer to string target to find
  * @paths: pointer to array of location to search
  *
  * Return: pointer to string absolute path else NULL
  */
char *search_path(char *path, char **paths)
{
	struct dirent *ent;
	struct stat st;
	DIR *dir;
	int index = 0;
	char *ans;

	if ((path[0] == '/') || (path[0] == '.'))
	{
		if ((lstat(path, &st) == -1) || (st.st_mode & S_IFMT) != S_IFREG)
			return (NULL);
		return (_strdup(path));
	}
	for (dir = opendir("./"); ((dir != NULL) && ((ent = readdir(dir)) != NULL));)
	{
		if (!_strcmp(ent->d_name, path))
		{
			closedir(dir);
			return (_strdup(path));
		}
	}
	closedir(dir);
	for (; (dir = opendir(paths[index])) != NULL; index++)
	{
		while ((ent = readdir(dir)) != NULL)
		{
			if (!_strcmp(ent->d_name, path))
			{
				ans = concat(3, paths[index], "/", path);
				closedir(dir);
				return (ans);
			}
		}
		closedir(dir);
	}
	return (NULL);
}

