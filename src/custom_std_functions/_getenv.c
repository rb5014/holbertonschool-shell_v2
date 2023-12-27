#include "custom_std_functions.h"

/**
 * _getenv - Retrieves the value of an environment variable.
 * @name: Name of the environment variable to retrieve.
 * @env: Array of strings representing the environment variables.
 * Description: Searches for the specified environment variable in the provided
 * environment array. If found, returns a pointer to the value part of the
 * variable (excluding its name and the '=' character).
 * Return: Pointer to the value of the environment variable,
 * or NULL if not found.
 */

char *_getenv(const char *name, char **env)
{
	int i = 0, j = 0;

	while (env[i] != NULL)
	{
		j = 0;
		while (name[j] == env[i][j])
		{
			if (name[j + 1] == '\0' && env[i][j + 1] == '=')
				return (&env[i][j + 2]);
			j++;
		}
		i++;
	}
	return (NULL);
}
