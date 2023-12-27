#include "custom_std_functions.h"

/**
 * update_env_var - Updates an existing environment variable.
 * @name: The name of the environment variable to update.
 * @value: The new value to set for the environment variable.
 * @env: Pointer to the array of environment variables.
 * Description: Searches for the environment variable by name in the array.
 * If found, updates its value. If not found, returns an error.
 * Return: 0 on successful update, -1 if variable not found or
 * memory allocation fails.
 */
int update_env_var(const char *name, const char *value, char ***env)
{
	char *new_env_var;
	int i = 0, j;

	for (i = 0; (*env)[i] != NULL; i++)
	{
		for (j = 0; name[j] == (*env)[i][j]; j++)
		{
			if (name[j + 1] == '\0' && (*env)[i][j + 1] == '=')
			{
				new_env_var = malloc(_strlen(name) + _strlen(value) + 2);
				if (new_env_var == NULL)
					return (-1);

				sprintf(new_env_var, "%s=%s", name, value);
				free((*env)[i]); /* Free the old value */
				(*env)[i] = new_env_var;
				return (0);
			}
		}
	}
	return (-1); /* Variable not found, should not happen */
}

/**
 * add_env_var - Adds a new environment variable.
 * @name: The name of the environment variable to add.
 * @value: The value of the environment variable to add.
 * @env: Pointer to the array of environment variables.
 * @env_size: The current size of the environment array.
 * Description: Allocates memory for a new environment variable
 * and appends it to the end of the environment array.
 * Updates the size of the environment array.
 * Return: 0 on success, -1 on memory allocation failure.
 */
int add_env_var(const char *name, const char *value, char ***env, int env_size)
{
	char *new_env_var;
	char **new_env = _realloc(*env, (env_size + 1) * sizeof(char *),
							  (env_size + 2) * sizeof(char *));
	if (new_env == NULL)
		return (-1);

	new_env_var = malloc(_strlen(name) + _strlen(value) + 2);
	if (new_env_var == NULL)
		return (-1);

	sprintf(new_env_var, "%s=%s", name, value);
	new_env[env_size] = new_env_var;
	new_env[env_size + 1] = NULL;

	*env = new_env; /* Update the environment array */
	return (0);
}

/**
 * _setenv - Sets or updates the value of an environment variable.
 * @name: The name of the environment variable to set/update.
 * @value: The value to set for the environment variable.
 * @overwrite: Flag to indicate if existing variables should be overwritten.
 * @env: Pointer to the array of environment variables.
 * Description: Checks if the environment variable exists.
 * If it does and overwrite is true, updates the variable.
 * If it does not exist, adds a new variable.
 * If the variable exists but overwrite is false, does nothing.
 * Return: 0 on success, -1 on failure or if the variable does not exist.
 */
int _setenv(const char *name, const char *value, int overwrite, char ***env)
{
	int env_size = 0;
	char *env_value = _getenv(name, *env);

	while ((*env)[env_size] != NULL)
		env_size++;

	if (env_value != NULL && overwrite)
	{
		return (update_env_var(name, value, env));
	} else if (env_value == NULL)
	{
		return (add_env_var(name, value, env, env_size));
	}

	/* If overwrite is false and variable exists, do nothing */
	return (0);
}
