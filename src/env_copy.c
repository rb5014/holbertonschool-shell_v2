#include "main.h"

char **copy_envp(char *original_envp[])
{
    int count, i;
	char **new_envp = NULL;

    for (count = 0; original_envp[count]; count++);

    new_envp = malloc((count + 1) * sizeof(char *));
    if (new_envp == NULL) {
        return NULL;
    }

    for (i = 0; i < count; i++)
	{
        new_envp[i] = strdup(original_envp[i]);
        if (new_envp[i] == NULL)
		{
            while (i--)
				free(new_envp[i]);
            free(new_envp);
            return NULL;
        }
    }
    new_envp[count] = NULL;

    return new_envp;
}

void free_env(char **env)
{
	int i;

	for (i = 0; env[i] != NULL; i++)
		free(env[i]);
	free(env[i]); /* last element is NULL but allocated so we free it too */

	free(env);
}

