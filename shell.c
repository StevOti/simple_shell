#include "shell.h"
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>

/**
* main - entry point.
* @ac: number of arguments.
* @av: array of command line arguments.
* @env: array of environment variables.
* Return: int
*/
int main(int ac, char **av, char **env)
{
	char line[4096] = {'c'}, *argv[4096];
	int i = 0;

	if (ac != 1 && av != NULL && env != NULL)
		return (1);

	if (isatty(STDIN_FILENO))
		write(STDOUT_FILENO, "$ ", 2);

	while (read(STDIN_FILENO, line, 4096) && *line != EOF)
	{
		argv[i] = str_tok(line, "\n");
		while (argv[i] != NULL)
		{
			i++;
			argv[i] = str_tok(NULL, "\n");
		}
		i = 0;

		while (argv[i] != NULL)
		{
			handle_line(argv[i], av[0], env);
			i++;
		}
		i = 0;

		while (line[i] != '\0')
		{
			line[i] = '\0';
			i++;
		}
		i = 0;

		if (isatty(STDIN_FILENO))
			write(STDOUT_FILENO, "$ ", 2);
	}
	if (isatty(STDIN_FILENO))
		write(STDOUT_FILENO, "\nexit\n", str_len("\nexit\n"));
	return (0);
}
