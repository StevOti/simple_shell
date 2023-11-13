#include "shell.h"

/**
 * handle_exit - function that handle the exit built in command.
 * @argv: list of command line strings
 * @parent_name: name of calling process.
 * Return void.
 */
void handle_exit(char **argv, char *parent_name)
{
	char err[4096] = {'\0'};
	int x = 0;

	str_cpy(&err[0], parent_name);
	str_cpy(&err[str_len(err)], ": ");

	while (argv[x])
		x++;

	if (x == 1)
	{
		write(STDERR_FILENO, "exit\n", str_len("exit\n"));
		exit(0);
	}
	else if (x == 2 && check_digit(argv[1]) == 0)
	{
		if (isatty(STDIN_FILENO))
			write(STDERR_FILENO, "exit\n", str_len("exit\n"));
		exit(string_to_int(argv[1]));
	}
	else if (x > 2 && check_digit(argv[1]) == 0)
	{
		str_cpy(&err[str_len(err)], "exit: too many arguments\n");
		write(STDERR_FILENO, err, str_len(err));
		return;
	}
	else
	{
		str_cpy(&err[str_len(err)], "exit: ");
		str_cpy(&err[str_len(err)], argv[1]);
		str_cpy(&err[str_len(err)], ": numeric argument required\n");
		write(STDERR_FILENO, err, str_len(err));
		exit(2);
	}
}
