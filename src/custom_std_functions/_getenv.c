#include "custom_std_functions.h"

/**
 * _getenv - retrieves the value of an environment variable.
 * @name: name of the environment variable.
 * Return: pointer to the value in the environment, or NULL if not found.
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
