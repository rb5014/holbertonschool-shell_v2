#include "main.h"
/**
 * _which - find exec in the path, change strings to get full pathname
 * @args: pointer of pointer to strings
 * @status: pointer of status to change if not found
 * Return: nothing
 */

int _which(char **args, int *status)
{
	char *path = getenv("PATH"), *copyenv, *cmdpath, *token, *envNULL;
	int lenarg, lentok;

	if (strchr(args[0], '/'))
		return (0);
	if (path)
	{
		copyenv = strdup(path);
		lenarg = strlen(args[0]);
		cmdpath = strdup(args[0]);
		envNULL = copyenv;
		while ((token = strtok(envNULL, ":")) != NULL)
		{
			envNULL = NULL;
			lentok = strlen(token);
			free(cmdpath);
			cmdpath = calloc((lentok + lenarg + 2), sizeof(char));
			cmdpath = strcpy(cmdpath, token);
			cmdpath = strcat(cmdpath, "/");
			cmdpath = strcat(cmdpath, args[0]);
			if (access(cmdpath, F_OK) == 0)
			{
				free(args[0]);
				args[0] = strdup(cmdpath);
				free(cmdpath);
				free(copyenv);
				return (0);
			}
		}
		free(cmdpath);
		free(copyenv);
	}
	write(STDERR_FILENO, "./hsh: 1: ", 10);
	write(STDERR_FILENO, args[0], strlen(args[0]));
	write(STDERR_FILENO, ": not found\n", 12);
	*status = 127;
	return (-1);
}
