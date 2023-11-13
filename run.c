#include "shell.h"
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>

/**
 * run_child - function that forks and runs a child process.
 * @parent_name: Name of the calling process.
 * @argv: list of arguments for execve
 * @env: environment variables that will be passed to execve
 * Return: zero on success 1 on failure
 */
void run_child(char *parent_name, char **argv, char **env)
{
	pid_t child_pid;
	int wstatus;
	struct stat st;
	char err[4096], *err_pt = &err[0];

	if (stat(argv[0], &st) != 0)
	{
		str_cpy(err_pt, parent_name);
		str_cpy((err_pt + str_len(err_pt)), ": ");
		str_cpy((err + str_len(err_pt)), argv[0]);
		perror(err_pt);
		return;
	}

	child_pid = fork();

	if (child_pid == -1)
	{
		perror("Error:");
		exit(1);
	}
	if (child_pid == 0)
	{
		if (execve(argv[0], argv, env) == -1)
		{
			perror(parent_name);
			exit(1);
		}
	}
	else
		wait(&wstatus);
}

/**
 * run - function that gets cmd tokens and runs the command.
 * @str: command line arguments.
 * @parent: name of parent program.
 * @env: environment variables.
 * Return: void.
*/
void run(char *str, char *parent, char **env)
{
	char *argv[4096], buff[4096] = {'\0'};
	int x = 0;

	argv[x] = str_tok(str, " ");

	while (argv[x] != NULL)
	{
		x++;
		argv[x] = str_tok(NULL, " ");
	}

	argv[x] = (char *) 0;

	str_cpy(buff, argv[0]);

	if (check_built_cmd(argv[0]) == 1)
		built_in_commands(argv, env, parent);
	else
	{
		argv[0] = paths(env, buff);
		run_child(parent, argv, env);
	}

	x = 0;
	while (buff[x])
	{
		buff[x] = '\0';
		x++;
	}
}
