#include "shell.h"

/**
 * str_tok - function that breaks up a string into tokens
 * @src: String that is to be broken up.
 * @delim: character specifiying where the string is to be broken.
 * Return: ret a pointer to a string token.
 */
char *str_tok(char *src, char *delim)
{
	static char *backup;
	char *ret;

	if (!src)
		src = backup;
	if (!src)
		return (NULL);

	while (1)
	{
		if (*src == *delim)
		{
			src++;
			continue;
		}

		if (*src == '\0')
			return (NULL);
		break;
	}
	ret = src;
	while (1)
	{
		if (*src == '\0')
		{
			backup = src;
			return (ret);
		}
		if (*src == *delim)
		{
			*src = '\0';
			backup = src + 1;
			return (ret);
		}
		src++;
	}
}
