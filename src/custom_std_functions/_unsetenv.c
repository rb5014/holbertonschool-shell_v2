#include "custom_std_functions.h"

/**
 * _unsetenv - Removes an environment variable from the given environment.
 * @name: Name of the environment variable to be removed.
 * @env: Pointer to the environment.
 * Return: 0 on success, -1 if the variable is not found.
 */
int _unsetenv(const char *name, char ***env)
{
	int i, j;

	for (i = 0; (*env)[i] != NULL; i++)
	{
		for (j = 0; name[j] == (*env)[i][j]; j++)
		{
			if (name[j + 1] == '\0' && (*env)[i][j + 1] == '=')
			{
				for (j = 0; (*env)[i][j] != '\0'; j++)
					(*env)[i][j] = '\0';
				return (0);
			}
		}
	}
	return (0);
}
