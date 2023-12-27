#include "main.h"

/**
 * copy_envp - Creates a copy of the environment variables array.
 * @original_envp: Array of strings representing the
 * original environment variables.
 * Description: Counts the number of environment variables
 * in the original array,
 * allocates memory for a new array of the same size,
 * and copies each environment
 * variable into the new array. Returns NULL if memory allocation fails.
 * Return: A pointer to the newly allocated array of environment variables.
 */
char **copy_envp(char *original_envp[])
{
	int count = 0, i;
	char **new_envp = NULL;

	while (original_envp[count])
		count++;

	new_envp = malloc((count + 1) * sizeof(char *));
	if (new_envp == NULL)
		return (NULL);

	for (i = 0; i < count; i++)
	{
		new_envp[i] = strdup(original_envp[i]);
		if (new_envp[i] == NULL)
		{
			while (i--)
				free(new_envp[i]);
			free(new_envp);
			return (NULL);
		}
	}
	new_envp[count] = NULL;

	return (new_envp);
}

/**
 * free_env - Frees memory allocated for an array of environment variables.
 * @env: Array of strings representing the environment variables.
 * Description: Iterates through the array, freeing each string. Also frees
 * the last element (NULL) and the array pointer itself.
 */
void free_env(char **env)
{
	int i;

	for (i = 0; env[i] != NULL; i++)
		free(env[i]);
	free(env[i]); /* last element is NULL but allocated so we free it too */

	free(env);
}

