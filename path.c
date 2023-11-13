#include "shell.h"
#include <sys/stat.h>

/**
 * paths - function that checks if a binary file is located in
 *	one of the directory in the path environment variable.
 * @env: list of environment variables.
 * @str: string input
 * Return: A pointee to the first directory contaning the binary @cmd_str
 *	or NULL if the it is not found.
 */
char *paths(char **env, char *str)
{
	char path[4096], *path_pt = &path[0], cmd[4096] = {'\0'}, dir[4096] = {'\0'};
	struct stat st;

	if (str == NULL)
		return (NULL);

	if (path_pt == NULL)
		return (NULL);

	str_cpy(path_pt, get_env("PATH", env));

	cmd[0] = '/';
	str_cpy(&cmd[1], str);

	str_cpy(&dir[0], str_tok(path, ":"));

	str_cpy(&dir[str_len(dir)], &cmd[0]);

	if (stat(dir, &st) == 0)
	{
		str_cpy(str, &dir[0]);
		return (str);
	}

	while (str_cpy(&dir[0], str_tok(NULL, ":")) != NULL)
	{

		str_cpy(&dir[str_len(dir)], &cmd[0]);

		if (stat(dir, &st) == 0)
		{
			str_cpy(str, &dir[0]);
			return (str);
		}
	}
	return (str);
}
