#include "main.h"
/**
 * _which - find exec in the path, change strings to get full pathname
 * @args: pointer of pointer to strings
 * @status: pointer of status to change if not found
 * Return: nothing
 */

int _which(char **args, int *status)
{
	char *path = _getenv("PATH"), *copyenv, *cmdpath, *token, *envNULL;
	int lenarg, lentok;

	if (_strchr(args[0], '/'))
		return (0);
	if (path)
	{
		copyenv = _strdup(path);
		lenarg = _strlen(args[0]);
		cmdpath = _strdup(args[0]);
		envNULL = copyenv;
		while ((token = strtok(envNULL, ":")) != NULL)
		{
			envNULL = NULL;
			lentok = _strlen(token);
			free(cmdpath);
			cmdpath = _calloc((lentok + lenarg + 2), sizeof(char));
			cmdpath = _strcpy(cmdpath, token);
			cmdpath = _strcat(cmdpath, "/");
			cmdpath = _strcat(cmdpath, args[0]);
			if (access(cmdpath, F_OK) == 0)
			{
				free(args[0]);
				args[0] = _strdup(cmdpath);
				free(cmdpath);
				free(copyenv);
				return (0);
			}
		}
		free(cmdpath);
		free(copyenv);
	}
	write(STDERR_FILENO, "./hsh: 1: ", 10);
	write(STDERR_FILENO, args[0], _strlen(args[0]));
	write(STDERR_FILENO, ": not found\n", 12);
	*status = 127;
	return (-1);
}
