#include "shell.h"

/**
* seperator - function that splits command line arguments
* at the semicolon.
* @str: command line argument.
* @parent: name of parent process.
* @env: list of environment variables.
* Return: void
*/

void seperator(char *str, char *parent, char **env)
{
	char *arr[4096], cpy[4096];
	int x = 0;

	arr[x] = str_tok(str, ";");

	while (arr[x] != NULL)
	{
		x++;
		arr[x] = str_tok(NULL, ";");
	}
	x = 0;
	while (arr[x] != NULL)
	{
		str_cpy(&cpy[0], arr[x]);
		logic_operators(&cpy[0], parent, env);
		x++;
	}
}
