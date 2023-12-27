#include "custom_std_functions.h"

int update_env_var(const char *name, const char *value, char ***env)
{
    char *new_env_var;
    int i = 0, j;

	for (i = 0; (*env)[i] != NULL; i++)
	{
		for(j = 0; name[j] == (*env)[i][j]; j++)
		{
			if (name[j + 1] == '\0' && (*env)[i][j + 1] == '=')
			{
				new_env_var = malloc(_strlen(name) + _strlen(value) + 2);
				if (new_env_var == NULL)
				{
					return (-1); /* Memory allocation failure */
				}
				sprintf(new_env_var, "%s=%s", name, value);
				free((*env)[i]); /* Free the old value */
				(*env)[i] = new_env_var;
				return (0);
			}
        }
    }
    return (-1); /* Variable not found, should not happen */
}

int add_env_var(const char *name, const char *value, char ***env, int env_size)
{
    char *new_env_var;
    char **new_env = _realloc(*env, (env_size + 1) * sizeof(char *),
							  (env_size + 2) * sizeof(char *));
    if (new_env == NULL)
	{
        return (-1); /* Memory allocation failure */
    }

    new_env_var = malloc(_strlen(name) + _strlen(value) + 2);
    if (new_env_var == NULL)
	{
        return (-1); /* Memory allocation failure */
    }
    sprintf(new_env_var, "%s=%s", name, value);
    new_env[env_size] = new_env_var;
    new_env[env_size + 1] = NULL;

    *env = new_env; /* Update the environment array */
    return (0);
}
/**
 * _setenv - retrieves the value of an environment variable.
 * @name: name of the environment variable.
 * Return: pointer to the value in the environment, or NULL if not found.
 */
int _setenv(const char *name, const char *value, int overwrite, char ***env)
{
    char *env_value = _getenv(name, *env);
    int env_size;

    for (env_size = 0; (*env)[env_size] != NULL; env_size++);

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
