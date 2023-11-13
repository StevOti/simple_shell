#include "shell.h"

/**
* str_len - function that gets the length of a string
* @str: String input
* Return: Int value length of string
*/

int str_len(char *str)
{
	int len = 0;
	char *cpy = str;

	while (*cpy)
	{
		len++;
		cpy++;
	}
	return (len);
}

/**
* str_dup - function that duplicates a string
* @str: string that is to be duplicated
* Return: a copy of the string str
*/
char *str_dup(char *str)
{
	char *dup = malloc(sizeof(char) * str_len(str) + 1);

	if (dup == NULL)
	{
		free(dup);
		return (NULL);
	}
	str_cpy(dup, str);
	return (dup);
}

/**
 * str_cpy - function that copies scr str to dest str
 * @dest: destination string.
 * @src: source string.
 * Return: pointer to destination string.
 */
char *str_cpy(char *dest, char *src)
{
	int x = 0;

	if (dest == NULL || src == NULL)
		return (NULL);
	while (src[x] != '\0')
	{
		dest[x] = src[x];
		x++;
	}
	dest[x] = '\0';
	return (dest);
}

/**
 * str_n_cpy - function that copies scr str to dest upto n characters.
 * @dest: destination string.
 * @src: source string.
 * @n: number of characters to copy.
 * Return: pointer to destination string.
 */
char *str_n_cpy(char *dest, char *src, int n)
{
	int x = 0;

	if (dest == NULL || src == NULL)
		return (NULL);
	while (src[x] != '\0' && x < n)
	{
		dest[x] = src[x];
		x++;
	}
	dest[x] = '\0';
	return (dest);
}

/**
 * str_cmp - function that compares two.
 * @s1: first input string
 * @s2: second input string
 * Return: if strings are equal it returns 0 if not -1
 */
int str_cmp(char *s1, char *s2)
{
	char *cpy_1 = s1, *cpy_2 = s2;

	while ((*cpy_1 && *cpy_2) && (*cpy_1 == *cpy_2))
	{
		cpy_1++;
		cpy_2++;

	}
	return (*cpy_1 - *cpy_2);
}
