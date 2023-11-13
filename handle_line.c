#include "shell.h"

/**
 * handle_line - function that handles line from read.
 * @lineptr: String gotten from the command line.
 * @env: list of environment variables.
 * @parent: name of the calling process.
 * Return: void
 */
void handle_line(char *lineptr, char *parent, char **env)
{
	char *arr[4096];
	int i = 0, x = 0;

	arr[i] = str_tok(lineptr, "\n");
	while (arr[i] != NULL)
	{
		i++;
		arr[i] = str_tok(NULL, "\n");
	}
	i = 0;
	while (arr[i] != NULL)
	{
		while (arr[i][x] != '\0' && arr[i][x] == ' ')
			x++;
		if (str_len(arr[i]) == x)
		{
			i++;
			continue;
		}
		seperator(arr[i], parent, env);
		i++;
		x = 0;
	}
	i = 0;
}
