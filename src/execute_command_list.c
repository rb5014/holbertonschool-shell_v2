#include "main.h"

void execute_command_list(int nb_cmds, command *cmd_list, char *prog_name,
						  char ***env, int *status, int *exit_flag)
{
	int i, wstatus = 0, std_fd_save = -1;
	char *full_path_cmd = NULL;

	for (i = 0; i < nb_cmds; i++)
	{
		if (cmd_list[i].file_op != NONE)
		{
			std_fd_save = do_redirection(&cmd_list[i], status);
			if (std_fd_save == -1)
				return;
		}
		if (is_builtin(prog_name, env, cmd_list[i].args,
					   cmd_list[i].nb_args, status, exit_flag) == 0)
		{
			*status = 0;
			full_path_cmd = _which(prog_name, *env, cmd_list[i].args, status);
			if (full_path_cmd)
			{
				execute_command(cmd_list, i, nb_cmds, env, full_path_cmd);
				free(full_path_cmd);
				if (i > 0)
				{
					if (cmd_list[i - 1].pipe_fd[0] != -1)
						close(cmd_list[i - 1].pipe_fd[0]);
					if (cmd_list[i - 1].pipe_fd[1] != -1)
						close(cmd_list[i - 1].pipe_fd[1]);
				}
				wait(&wstatus);
				*status = WEXITSTATUS(wstatus);
			}
		}
		if (*exit_flag == -1)
			break;
		if (cmd_list[i].file_op != NONE)
			do_revert_redirection(&cmd_list[i], std_fd_save);
		if (*status && (cmd_list[i].logical_op == AND))
			break;
		if ((*status == 0) && (cmd_list[i].logical_op == OR))
			break;
	}
}

void execute_command(command *cmd_list, int i, int nb_cmds, char ***env,
					 char *full_path_cmd)
{
	pid_t pid = fork();

	if (pid == 0)
	{ /* Child process */
		if (cmd_list[i].pipe_op == PIPE)
		{
			int input_fd = (i == 0) ? -1 : cmd_list[i - 1].pipe_fd[0];
			int is_last = (i == nb_cmds - 1);
			int output_fd = is_last ? -1 : cmd_list[i].pipe_fd[1];

			/* Setup input and output for the current command */
			if (input_fd != -1 && (cmd_list[i].file_op != FROM_FILE)
				&& (cmd_list[i].file_op != HERE_DOCUMENT))
			{
				dup2(input_fd, STDIN_FILENO);
			}
			if ((output_fd != -1) && (cmd_list[i].file_op != TO_FILE)
				&& (cmd_list[i].file_op != TO_FILE_APPEND))
			{
				dup2(cmd_list[i].pipe_fd[1], STDOUT_FILENO);
			}
		}
		/* Child close all pipe file descriptors */
		close_all_pipes(cmd_list, nb_cmds);

		/* Execute the command */
		if (execve(full_path_cmd, cmd_list[i].args, *env) == -1)
		{
			perror("./shell");
		}
	}
	else if (pid < 0)
	{
		perror("fork");
	}
}

/**
 * close_all_pipes - Closes all pipe file descriptors in a command list.
 * @cmd_list: Pointer to the command list.
 * @nb_cmds: Number of commands in the list.
 */
void close_all_pipes(command *cmd_list, int nb_cmds)
{
	int i;

	/* Close all pipe file descriptors */
	for (i = 0; i < nb_cmds; i++)
	{
		if (cmd_list[i].pipe_fd[0] != -1)
		{
			close(cmd_list[i].pipe_fd[0]);
		}
		if (cmd_list[i].pipe_fd[1] != -1)
		{
			close(cmd_list[i].pipe_fd[1]);
		}
	}
}

/**
 * is_builtin - Checks if a command is a built-in command.
 * @prog_name: Name of the program.
 * @env: Pointer to array of environment variables.
 * @args: Array of strings representing the arguments passed to the program.
 * @nb_args: Number of arguments.
 * @status: Pointer to an int representing the program's exit status.
 * @exit_flag: Pointer to an int flag that will break the program loop.
 * Description: Checks if the command is 'env', 'exit', or 'cd' and executes
 * the corresponding function. For 'exit', updates the exit flag in main.
 * Return: 1 if a built-in command is found and executed, -1 for 'exit',
 * 0 if no built-in command is found.
 */
int is_builtin(char *prog_name, char ***env, char **args,
			   int nb_args, int *status, int *exit_flag)
{
	if (_strcmp(args[0], "env") == 0)
	{
		do_env(*env);
		return (1);
	}
	if (_strcmp(args[0], "setenv") == 0)
	{
		do_setenv(env, args, nb_args);
		return (1);
	}
	if (_strcmp(args[0], "unsetenv") == 0)
	{
		do_unsetenv(env, args, nb_args);
		return (1);
	}
	else if (_strcmp(args[0], "exit") == 0)
	{
		do_exit(prog_name, args, nb_args, status);
		*exit_flag = -1;
		return (1);
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
char *_which(char *prog_name, char **env, char **args, int *status)
{
	char *path = _getenv("PATH", env), *copyenv, *cmdpath, *token, *envNULL;
	int lenarg, lentok;
	char *full_path_cmd = NULL;

	if (_strchr(args[0], '/'))
		return (_strdup(args[0]));
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
				full_path_cmd = _strdup(cmdpath);
				break;
			}
		}
		free(cmdpath);
		free(copyenv);
	}
	if (!full_path_cmd)
	{
		*status = 127;
		print_error_message(prog_name, args[0], NULL, *status);
	}
	return (full_path_cmd);
}
