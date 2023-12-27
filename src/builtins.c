#include "main.h"

/**
 * do_env - Prints all environment variables and their contents.
 * @env: Array of strings representing the environment variables.
 * Description: Iterates through the array of environment variables and
 * prints each one to the standard output.
 */
void do_env(char **env)
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


char *determine_new_directory(char *prog_name, char **args, int nb_args,
							  char ***env, int *status, int *old_dir_flag)
{
	char *new_dir = NULL;

	if (nb_args > 1)
	{
		if (_strcmp(args[1], "-") == 0)
		{
			new_dir = _getenv("OLDPWD", *env);
			*old_dir_flag = 1;
		}
		else
			new_dir = args[1];
	}
	else
	{
		new_dir = _getenv("HOME", *env);
		if (!new_dir)
		{
			*status = 1;
			print_error_message(prog_name, args[0], "HOME", *status);
		}
	}
	return (new_dir);
}

int change_directory(char *prog_name, char **args, char *new_dir,
					 char *cur_dir, char ***env, int old_dir_flag, int *status)
{
	char *abs_new_dir = NULL;

	if (chdir(new_dir) == -1)
	{
		if (errno == ENOENT)
			print_error_message(prog_name, args[0], args[1], *status);

		return (-1);
	}
	else
	{
		if (old_dir_flag)
			printf("%s\n", new_dir);
		abs_new_dir = getcwd(abs_new_dir, 0);
		_setenv("PWD", abs_new_dir, 1, env);
		free(abs_new_dir);
		_setenv("OLDPWD", cur_dir, 1, env);
	}
	return (0);
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
	char *cur_dir = NULL, *new_dir = NULL;
	int old_dir_flag = 0;

	cur_dir = getcwd(cur_dir, 0);
	new_dir = determine_new_directory(prog_name, args, nb_args, env,
									  status, &old_dir_flag);

	if ((!new_dir) || (change_directory(prog_name, args, new_dir, cur_dir,
									 env, old_dir_flag, status) == -1))
	{
		free(cur_dir);
		return (0);
	}

	free(cur_dir);
	return (1);
}



