#include "shell.h"

/**
 * check_built_cmd - function that checks for built in commands
 * @str: command line argument.
 * Return: 1 if a builtin argument is found 0 if none is found
 */
int check_built_cmd(char *str)
{
	if (str == NULL)
		return (0);
	if (str_cmp(str, "setenv") == 0)
		return (1);
	if (str_cmp(str, "unsetenv") == 0)
		return (1);
	if (str_cmp(str, "exit") == 0)
		return (1);
	if (str_cmp(str, "cd") == 0)
		return (1);
	if (str_cmp(str, "env") == 0)
		return (1);
	if (str_cmp(str, "alias") == 0)
		return (1);
	return (0);
}
/**
 * string_to_int - function that converts a string to an int.
 * @str: string to be converted.
 * Return: str as an int.
 */
int string_to_int(char *str)
{
	int num = 0, i = 0;

	for (; str[i] != '\0'; i++)
	{
		num = num * 10 + (str[i] - 48);
	}
	return (num);
}
/**
 * check_digit - function that checks if all character in a string are digits.
 * @str: string inputt.
 * Return: 0 if all are string else -1.
 */
int check_digit(char *str)
{
	int x = 0;

	while (str[x] != '\0')
	{
		if (str[x] >= '0' && str[x] <= '9')
		{
			x++;
			continue;
		}
		return (-1);
	}
	return (0);
}

/**
 * built_in_commands - function that handles shell built in commands.
 * @argv: list of cli arguments.
 * @env: list of environment variables.
 * @parent_name: name of calling process.
 * Return: void.
 */
void built_in_commands(char **argv, char **env, char *parent_name)
{
	if (str_cmp(argv[0], "exit") == 0)
	{
		handle_exit(argv, parent_name);
		return;
	}
	if (str_cmp(argv[0], "setenv") == 0)
		set_env(argv, env, parent_name);

	if (str_cmp(argv[0], "unsetenv") == 0)
		unset_env(argv, env, parent_name);

	if (str_cmp(argv[0], "cd") == 0)
		handle_cd(argv, env, parent_name);

	if (str_cmp(argv[0], "env") == 0)
	{
		int x = 0;

		while (env[x] != NULL)
		{
			write(STDOUT_FILENO, env[x], str_len(env[x]));
			write(STDOUT_FILENO, "\n", 1);
			x++;
		}
	}
	if (str_cmp(argv[0], "alias") == 0)
		handle_alias(argv, parent_name);
}
