#include "shell.h"

/**
 * get_env - function path gets a shell environment variable.
 * @env_name: name of the environemt variable you want to get.
 * @env: list of environment variable strings.
 * Return: string pointer to the environemt variable or NULL
 *	if it is not found.
 */

char *get_env(char *env_name, char **env)
{
	int x = 0, i = 0;

	while (env[x] != NULL)
	{
		while (env_name[i] != '\0')
		{
			if (env[x][i] == env_name[i])
			{
				if (env_name[i + 1] == '\0' && env[x][i + 1] == '=')
				{
					i += 2;
					return (env[x] + i);
				}
				i++;
				continue;
			}
			break;
		}
		x++;
	}
	return (NULL);
}
