#include "shell.h"
#include <sys/stat.h>

/**
 * logic_operators - function that gets cmd tokens and runs the command.
 * @str: command line arguments.
 * @parent: name of parent program.
 * @env: environment variables.
 * Return: void.
*/
void logic_operators(char *str, char *parent, char **env)
{
	char buff[4096], *arr[4096];
	int i = 0;
	struct stat st;

	arr[i] = str_tok(str, "&&");

	while (arr[i] != NULL)
	{
		i++;
		arr[i] = str_tok(NULL, "&&");
	}
	i = 0;
	while (arr[i] != NULL)
	{
		str_cpy(&buff[0], arr[i]);
		if (stat(paths(env, str_tok(buff, " ")), &st) == 0)
			run(arr[i], parent, env);
		else
		{
			run(arr[i], parent, env);
			break;
		}
		i++;
	}
}
