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

void do_setenv(char ***env, char **args, int nb_args)
{
	if (nb_args >= 3)
		_setenv(args[1], args[2], 1, env);
}

void do_unsetenv(char ***env, char **args, int nb_args)
{
		if (nb_args >= 2)
		_unsetenv(args[1], env);
}