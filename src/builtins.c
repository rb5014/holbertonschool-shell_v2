#include "main.h"
/**
 * printenv - print all environment variables and their content
 */
void printenv(char **env)
{
	int i = 0;

	while (env[i] != NULL)
	{
		printf("%s\n", env[i]);
		i++;
	}
}

/**
 * do_exit - print error message if any and update exit code
 * @prog_name: name of the program
 * @args: args to check if it is "exit"
 * @nb_args: number of args
 * @status: pointer of status to change if error
 * Return: 1 if found, 0 if not
 */
void do_exit(char *prog_name, char **args, int nb_args, int *status)
{
	if (nb_args > 1)
	{
		if (_isnumber(args[1]))
		{
			int num = _atoi(args[1]);

			if (num < 0)
			{
				*status = 2;
				print_error_message(prog_name, args[0], args[1], *status);
			}
			else if (num > 255)
				*status = 232;
			else
				*status = num;
		}
		else
		{
			*status = 2;
			print_error_message(prog_name, args[0], args[1], *status);
		}
	}
}

/**
 * do_cd - change the current working directory
 * @prog_name: name of the program
 * @args: args to check if it is "cd"
 * @nb_args: number of args
 * @status: pointer of status to change if error
 * Return: 1 if found, 0 if not
 */
int do_cd(char *prog_name, char ***env, char **args, int nb_args, int *status)
{
	char *cur_dir = NULL, *new_dir = NULL, *abs_new_dir = NULL;
	cur_dir = getcwd(cur_dir, 0);

	if (nb_args > 1)
	{
		if (_strcmp(args[1], "-") == 0)
		{
			new_dir = _getenv("OLDPWD", *env);
		}
		else
			new_dir = args[1];
	}
	else
	{
		new_dir = _getenv("HOME", *env);
	}
	if (chdir(new_dir) == -1)
	{
		if (errno == ENOENT)
		{
			print_error_message(prog_name, args[0], args[1], *status);
		}
	}
	else
	{
		abs_new_dir = getcwd(abs_new_dir, 0);
		_setenv("PWD", abs_new_dir, 1, env);
		free(abs_new_dir);
		_setenv("OLDPWD", cur_dir, 1, env);
	}
	free(cur_dir);
	return (0);
}

/**
 * is_builtin - if builtin found
 * @prog_name: name of the program
 * @args: args to check if it is "exit"
 * @nb_args: number of args
 * @status: pointer of status to change if error
 * Return: 1 if found, 0 if not
 */
int is_builtin(char *prog_name, char ***env, char **args, int nb_args, int *status)
{
	if (_strcmp(args[0], "env") == 0)
	{
		printenv(*env);
		return (1);
	}
	else if (_strcmp(args[0], "exit") == 0)
	{
		do_exit(prog_name, args, nb_args, status);
		return (-1); /* -1 to update exit_flag in main */
	}
	else if (_strcmp(args[0], "cd") == 0)
	{
		if (do_cd(prog_name, env, args, nb_args, status) == 0)
			return (1);
		else
			return (-1);
	}
	return (0);
}
