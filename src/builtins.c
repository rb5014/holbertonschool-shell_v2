#include "main.h"

/**
 * printenv - Prints all environment variables and their contents.
 * @env: Array of strings representing the environment variables.
 * Description: Iterates through the array of environment variables and
 * prints each one to the standard output.
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
 * do_exit - Checks if 'exit' command is valid and updates exit code.
 * @prog_name: Name of the program.
 * @args: Array of strings representing the arguments passed to the program.
 * @nb_args: Number of arguments.
 * @status: Pointer to an int representing the program's exit status.
 * Description: If 'exit' command is valid,
 * updates the exit status accordingly.
 * Prints an error message if the exit status is invalid.
 * Return: 1 if 'exit' command is found, 0 otherwise.
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
 * do_cd - Changes the current working directory.
 * @prog_name: Name of the program.
 * @env: Pointer to array of environment variables.
 * @args: Array of strings representing the arguments passed to the program.
 * @nb_args: Number of arguments.
 * @status: Pointer to an int representing the program's exit status.
 * Description: Changes the working directory based on the given argument.
 * Updates the PWD and OLDPWD environment variables. Prints error message
 * if directory change fails.
 * Return: 1 if directory change is successful, 0 otherwise.
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
 * is_builtin - Checks if a command is a built-in command.
 * @prog_name: Name of the program.
 * @env: Pointer to array of environment variables.
 * @args: Array of strings representing the arguments passed to the program.
 * @nb_args: Number of arguments.
 * @status: Pointer to an int representing the program's exit status.
 * Description: Checks if the command is 'env', 'exit', or 'cd' and executes
 * the corresponding function. For 'exit', updates the exit flag in main.
 * Return: 1 if a built-in command is found and executed, -1 for 'exit',
 * 0 if no built-in command is found.
 */
int is_builtin(char *prog_name, char ***env, char **args,
			   int nb_args, int *status)
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
