#include "main.h"

/**
 * do_cmd - Tries to execute a command.
 * @prog_name: The name of the program.
 * @env: Pointer to the environment variables.
 * @status: Pointer to an int to store the status of the command execution.
 * @args: Array of strings representing the command and its arguments.
 * @nb_args: Number of arguments in 'args'.
 * @exit_flag: Pointer to an int that signals if the program should exit.
 * Description: Checks if the command is a built-in function and executes it.
 * If not, tries to locate the command and execute it.
 * Updates 'exit_flag' if needed.
 */
void do_cmd(char *prog_name, char ***env, int *status, command cmd, int *exit_flag)
{
	int builtin_flag = 0, std_fd_save = -1;

	if (cmd.op != NONE)
	{
		std_fd_save = do_redirection(cmd.op, cmd.file_for_redir, cmd.args[0]);
		if (std_fd_save == -1)
		{
			*status = -1;
			return;
		}
	}
	
	builtin_flag = is_builtin(prog_name, env, cmd.args, cmd.nb_args, status);
	if (builtin_flag == 0)
	{
		if ((_which(prog_name, *env, cmd.args, status) == 0))
			fork_wait_execve(env, cmd.args, status);

	}
	else if (builtin_flag == -1)
		*exit_flag = builtin_flag;
	if (cmd.op != NONE)
		do_revert_redirection(cmd.op, std_fd_save);

}

/**
 * is_builtin - Checks if a command is a built-in command.
 * @prog_name: Name of the program.
 * @env: Pointer to array of environment variables.
 * @args: Array of strings representing the arguments passed to the program.
 * @nb_args: Number of arguments.
 * @status: Pointer to an int representing the program's exit status.
 * Description: Checks if the command is 'env', 'exit', or 'cd' and executes
 * the corresponding function. For 'exit', updates the exit flag in main.
 * Return: 1 if a built-in command is found and executed, -1 for 'exit',
 * 0 if no built-in command is found.
 */
int is_builtin(char *prog_name, char ***env, char **args,
			   int nb_args, int *status)
{
	if (_strcmp(args[0], "env") == 0)
	{
		do_env(*env);
		return (1);
	}
	else if (_strcmp(args[0], "exit") == 0)
	{
		do_exit(prog_name, args, nb_args, status);
		return (-1); /* -1 to update exit_flag in main */
	}
	else if (_strcmp(args[0], "cd") == 0)
	{
		if (do_cd(prog_name, env, args, nb_args, status) == 1)
			return (1);
		else
			return (-1);
	}
	return (0);
}

/**
 * _which - Finds the executable in the PATH and
 * updates the command with its full pathname.
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
