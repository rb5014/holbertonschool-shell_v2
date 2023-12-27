#include "main.h"

/**
 * _which - Finds the executable in the PATH and
 *          updates the command with its full pathname.
 * @prog_name: Name of the program.
 * @env: Array of environment variables.
 * @args: Pointer to an array of strings,
 * where the first element is the command to find.
 * @status: Pointer to an int that stores the status of the operation.
 * Description: Checks if the command (args[0]) is in the PATH.
 * If it is, updates args[0] with the full path of the command.
 * If the command is not found in the PATH or an error occurs,
 * updates the status to 127 and prints an error message.
 * Return: 0 if the command is found in the PATH,
 *         -1 if not found or an error occurs.
 */
int _which(char *prog_name, char **env, char **args, int *status)
{
	char *path = _getenv("PATH", env), *copyenv, *cmdpath, *token, *envNULL;
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
			if ((access(cmdpath, F_OK) == 0))
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
	*status = 127;
	print_error_message(prog_name, args[0], NULL, *status);
	return (-1);
}

/**
 * fork_wait_execve - Forks a child process to execute a command.
 * @env: Pointer to the environment variables.
 * @p: Pointer to the array of strings representing
 * the command and its arguments.
 * @status: Pointer to an int to store the exit status of the child process.
 * Description: Creates a child process using fork(). In the child process,
 * executes a command using execve().
 * The parent process waits for the child to finish
 * and stores its exit status.
 */
void fork_wait_execve(char ***env, char **p, int *status)
{
	pid_t child = 0;
	int wstatus;

	child = fork();
	if (child == 0)
	{
		if (execve(p[0], p, *env) == -1)
		{
			perror("./shell");
		}
	}
	else
	{
		wait(&wstatus);
		*status = WEXITSTATUS(wstatus);
	}
}
