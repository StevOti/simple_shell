#include "shell.h"


/**
 * update_dir - function that updates the OLDPWD and PWD env vaiables.
 * @var_name: name of environment variable.
 * @new_value: value it will be updated to.
 * @env: list of environment variables.
 * @parent_name: name of calling process.
 * Return: void.
 */
void update_dir(char *var_name, char *new_value,
		char *parent_name, char **env)
{
	char *av[4];

	av[0] = "setenv";
	av[1] = var_name;
	av[2] = new_value;
	av[3] = (char *) 0;
	set_env(av, env, parent_name);
}
/**
 * default_option - function that runs the default option.
 * @argv: list of cli arguments.
 * @env: list of environment variables.
 * @parent_name: name of calling process.
 * @err_msg: error message
 * Return: void.
 */
void default_option(char **argv, char *parent_name,
		char **env, char *err_msg)
{
	char err[4096] = {'\0'};
	char *cur_dir = get_env("PWD", env);

	if (chdir(argv[1]) == 0)
	{
		update_dir("PWD", argv[1], parent_name, env);
		update_dir("OLDPWD", cur_dir, parent_name, env);
	}
	else
	{
		str_cpy(&err[0], err_msg);
		str_cpy(&err[str_len(err)], ": ");
		str_cpy(&err[str_len(err)], argv[1]);
		str_cpy(&err[str_len(err)], ": No such file or directory\n");
		write(STDERR_FILENO, err, str_len(err));
	}

}
/**
 * handle_cd - function that handles the built in commands.
 * @argv: list of cli arguments.
 * @env: list of environment variables.
 * @parent_name: name of calling process.
 * Return: void.
 */
void handle_cd(char **argv, char **env, char *parent_name)
{
	int x = 0;
	char err[4096];

	str_cpy(&err[0], parent_name);
	str_cpy(&err[str_len(err)], ": ");
	str_cpy(&err[str_len(err)], argv[0]);
	while (argv[x])
		x++;
	if (x > 2)
	{
		str_cpy(&err[str_len(err)], ": too many arguments\n");
		write(STDERR_FILENO, err, str_len(err));
	}
	if (x == 1)
	{
		char *cur_dir = get_env("PWD", env);

		if (chdir(get_env("HOME", env)) == 0)
		{
			update_dir("OLDPWD", cur_dir, parent_name, env);
			update_dir("PWD", get_env("HOME", env), parent_name, env);
		}
	}
	if (x == 2)
	{
		char *cur_dir = get_env("PWD", env);

		if (str_cmp(argv[1], "-") == 0)
		{
			if (chdir(get_env("OLDPWD", env)) == 0)
			{
				update_dir("PWD", get_env("PWD", env), parent_name, env);
				update_dir("OLDPWD", cur_dir, parent_name, env);
			}
		}
		else
			default_option(argv, parent_name, env, &err[0]);
	}
}
