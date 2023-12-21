#include "main.h"
/**
 * is_env - prints environment variables if env found
 * @arg: arg to check
 * Return: 0 if found, -1 if not or error
 */

int is_env(char *arg)
{
	if (arg && _strcmp(arg, "env") == 0)
	{
		printenv();
		return (0);
	}
	return (-1);
}

/**
 * is_exit - if exit found, free arg and return 0
 * @prog_name: name of the program
 * @args: args to check if it is "exit"
 * @nb_args: number of args
 * @status: pointer of status to change if error
 * Return: 1 if found, 0 if not
 */
int is_exit(char *prog_name, char **args, int nb_args, int *status)
{
	if (_strcmp(args[0], "exit") == 0)
	{
		if (nb_args > 1)
		{
			if (_isnumber(args[1]))
			{
				int num = _atoi(args[1]);

				if ((num >= 0) && (num <= 255))
					*status = num;
				else
				{
					*status = 2;
					print_error_message(prog_name, args[0], args[1], *status);
				}
			}
			else
			{
				*status = 2;
				print_error_message(prog_name, args[0], args[1], *status);
			}
		}

		return (1);
	}
	return (0);
}

/**
 * is_cd - if cd found, change the current working directory
 * @arg: arg to check if it is cd
 * Return: 1 if found, 0 if not
 */
int is_cd(char *arg)
{
	if (_strcmp(arg, "cd") == 0)
		return (1);
	return (0);
}
