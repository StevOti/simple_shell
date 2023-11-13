#include "shell.h"

/**
 * print_err - function that prints the error message.
 * @str: name of missing alias
 * @parent: name of parent process
 * Return: void.
 */
void print_err(char *str, char *parent)
{
	char err[4096] = {'\0'};

	str_cpy(&err[0], parent);
	str_cpy(&err[str_len(err)], ": alias: ");
	str_cpy(&err[str_len(err)], str);
	str_cpy(&err[str_len(err)], ": not found\n");
	write(STDOUT_FILENO, err, str_len(err));
}
/**
 * print_alias - function that prints aliases.
 * @arr: list of aliases
 * Return: void.
 */
void print_alias(char arr[4096][1000])
{
	int len = 0;
	char buff[4096] = {'\0'};

	while (arr[len][0] != '\0')
	{
		if (isatty(STDIN_FILENO))
			str_cpy(&buff[0], "alias ");
		str_cpy(&buff[str_len(buff)], arr[len]);
		str_cpy(&buff[str_len(buff)], "\n");
		write(STDOUT_FILENO, buff, str_len(buff));
		len++;
	}
}

/**
 * add_quotation - function that handles alias built in commands.
 * @dest: dest string.
 * @str: source string.
 * Return: void.
 */
void add_quotation(char *dest, char *str)
{
	int x = 0;

	while (*str != '\0')
	{
		if (*str == '\'')
		{
			x++;
			str++;
			continue;
		}
		*dest++ = *str++;
		if (x == 2)
			break;
	}
	str_cpy(&dest[str_len(dest)], "'");
}

/**
 * handle_alias - function that handles alias built in commands.
 * @argv: list of cli arguments.
 * @parent: name of calling process.
 * Return: void.
 */
void handle_alias(char **argv, char *parent)
{
	static char arr[4096][1000], cpy[4096] = {'\0'}, name[4096] = {'\0'};
	int x = 0, len = 0, index = 0;

	while (argv[x] != NULL)
		x++;
	if (x == 1)
		print_alias(arr);
	len = x = 0;
	while (argv[len] != NULL)
	{
		index = 0;
		while (argv[len][x] != '\0' && argv[len][x] != '=')
			x++;
		if (argv[len][x] == '=')
		{
			str_n_cpy(&name[0], argv[len], x);
			str_n_cpy(&cpy[0], arr[index], x);
			if (argv[len][x + 1] != '\'')
			while (arr[index][0] != '\0')
			{
				if (str_cmp(name, cpy) == 0)
				{
					str_cpy(&name[str_len(name)], "='");
					add_quotation(&name[str_len(name)], &argv[len][x + 1]);
					str_cpy(&arr[index][0], name);
					return;
				}
				str_n_cpy(&cpy[0], arr[index], x);
				index++;
			}
			str_cpy(&name[str_len(name)], "='");
			add_quotation(&name[str_len(name)], &argv[len][x + 1]);
			str_cpy(&arr[index][0], name);
			return;
		}
		if (len >= 1)
			print_err(argv[len], parent);
		x = 0;
		len++;
	}
}
