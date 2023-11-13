#include "shell.h"
#include <signal.h>

/**
 * set_env - function that handles setenv built in command.
 * @argv: list of cli arguments.
 * @env: list of environment variables.
 * @parent_name: name of calling process.
 * Return: void.
 */
int set_env(char **argv, char **env, char *parent_name)
{
	int x = 0, env_len = 0;
	char new_env[4096] = {'\0'}, err[4096] = {'\0'}, str[4096] = {'\0'};

	while (argv[x])
		x++;
	str_cpy(&err[0], parent_name);
	str_cpy(&err[str_len(err)], ": ");
	str_cpy(&err[str_len(err)], "setenv: ");

	if (x != 3)
	{
		x > 3 ? str_cpy(&err[str_len(err)], "Too many arguments\n")
		: str_cpy(&err[str_len(err)], "Fewer arguments than expected\n");
		write(STDERR_FILENO, err, str_len(err));
		return (-1);
	}
	while (env[env_len] != NULL)
	{
		str_cpy(&str[0], env[env_len]);
		if (str_cmp(str_tok(str, "="), argv[1]) == 0)
			break;
		env_len++;
	}
	if (env[env_len] == NULL)
	{
		str_cpy(&new_env[0], argv[1]);
		str_cpy(&new_env[str_len(new_env)], "=");
		str_cpy(&new_env[str_len(new_env)], argv[2]);
		env[env_len] = str_dup(new_env);
		env[env_len + 1] = (char *) 0;
		return (0);
	}
	else
	{
		str_cpy(&new_env[0], argv[1]);
		str_cpy(&new_env[str_len(new_env)], "=");
		str_cpy(&new_env[str_len(new_env)], argv[2]);
		env[env_len] = str_dup(new_env);
		return (0);
	}
}

/**
 * unset_env - function that handles unsetenv built in command.
 * @argv: list of cli arguments.
 * @env: list of environment variables.
 * @parent_name: name of calling process.
 * Return: void.
 */
int unset_env(char **argv, char **env, char *parent_name)
{
	int len = 0, x = 0;
	char err[4096] = {'\0'}, str[4096] = {'\0'};

	while (argv[x])
		x++;

	str_cpy(&err[0], parent_name);
	str_cpy(&err[str_len(err)], ": ");
	str_cpy(&err[str_len(err)], "unsetenv: ");
	if (x > 2 || x < 2)
	{
		x > 2 ? str_cpy(&err[str_len(err)], "Too many arguments\n")
		: str_cpy(&err[str_len(err)], "Fewer arguments than expected\n");
		write(STDERR_FILENO, err, str_len(err));
		return (-1);
	}
	if (env[len] == NULL)
		return (0);

	while (env[len] != NULL)
	{
		str_cpy(&str[0], env[len]);
		if (str_cmp(str_tok(str, "="), argv[1]) == 0)
			break;
		len++;
	}
	if (env[len] != NULL)
	{
		if (env[len + 1] != NULL)
			env[len] = env[len + 1];
		else
			env[len] = (char *) 0;
	}
	return (0);
}
