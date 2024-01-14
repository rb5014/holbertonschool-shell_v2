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
		if (_strlen(env[i]) > 0)
			printf("%s\n", env[i]);
		i++;
	}
}

/**
 * do_setenv - Set or update an environment variable in the given environment.
 * @env: Pointer to the environment.
 * @args: Array of arguments containing variable name and value.
 * @nb_args: Number of arguments provided.
 */
void do_setenv(char ***env, char **args, int nb_args)
{
	if (nb_args >= 3)
		_setenv(args[1], args[2], 1, env);
}

/**
 * do_unsetenv - Unset or remove an environment variable
 * from the given environment.
 * @env: Pointer to the environment.
 * @args: Array of arguments containing the variable name to unset.
 * @nb_args: Number of arguments provided.
 */
void do_unsetenv(char ***env, char **args, int nb_args)
{
		if (nb_args >= 2)
		_unsetenv(args[1], env);
}
