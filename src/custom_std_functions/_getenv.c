#include "custom_std_functions.h"

/**
 * _getenv - retrieves the value of an environment variable.
 * @name: name of the environment variable.
 * Return: pointer to the value in the environment, or NULL if not found.
 */
char *_getenv(const char *name)
{
	int i = 0, j = 0;

	while (environ[i] != NULL)
	{
		j = 0;
		while (name[j] == environ[i][j])
		{
			if (name[j + 1] == '\0' && environ[i][j + 1] == '=')
				return (&environ[i][j + 2]);
			j++;
		}
		i++;
	}
	return (NULL);
}
