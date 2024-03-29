#include "main.h"

/**
 * do_redirection - Handle input/output redirection based on command's file_op.
 * @cmd: Pointer to the command structure.
 * @status: Pointer to the status variable.
 * Return: Saved standard file descriptor or -1 on failure.
 */
int do_redirection(command *cmd, int *status)
{
	int std_fd_save = -1;

	switch ((*cmd).file_op)
	{
	case TO_FILE:
		std_fd_save = dup(STDOUT_FILENO);
		stdout_to_file(cmd, 0);
		break;

	case TO_FILE_APPEND:
		std_fd_save = dup(STDOUT_FILENO);
		stdout_to_file(cmd, 1);
		break;

	case HERE_DOCUMENT:
		gen_temp_heredoc_file(cmd);
		std_fd_save = dup(STDIN_FILENO);
		if (stdin_from_file(cmd, status) == -1)
			return (-1);
		break;

	case FROM_FILE:
		std_fd_save = dup(STDIN_FILENO);
		if (stdin_from_file(cmd, status) == -1)
			return (-1);
		break;

	default:
		break;
	}
	return (std_fd_save);
}

/**
 * do_revert_redirection - Revert redirection based on command's file_op.
 * @cmd: Pointer to the command structure.
 * @std_fd_save: Saved standard file descriptor.
 */
void do_revert_redirection(command *cmd, int std_fd_save)
{
	switch ((*cmd).file_op)
	{
	case TO_FILE:
	case TO_FILE_APPEND:
		if (dup2(std_fd_save, STDOUT_FILENO) == -1)
		{
			perror("dup2");
		}
		break;
	case FROM_FILE:
	case HERE_DOCUMENT:
		if ((*cmd).fd != -1)
			unlink((*cmd).file_for_redir);
		if (dup2(std_fd_save, STDIN_FILENO) == -1)
		{
			perror("dup2");
		}
		break;

	default:
		if ((*cmd).fd != -1)
			close((*cmd).fd);
		break;
	}
}

/**
 * stdout_to_file - Redirect standard output to a file.
 * @cmd: Pointer to the command structure.
 * @is_append: Flag indicating whether to append or truncate the file.
 * Return: 0 on success, -1 on failure.
 */
int stdout_to_file(command *cmd, int is_append)
{

	if ((is_append != 0))
		(*cmd).fd = open((*cmd).file_for_redir,
						 O_CREAT | O_WRONLY | O_APPEND, S_IRWXU);
	else
		(*cmd).fd = open((*cmd).file_for_redir,
						 O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
	if (dup2((*cmd).fd, STDOUT_FILENO) == -1)
	{
		perror("dup2");
		return (-1);
	}
	return (0);
}

/**
 * stdin_from_file - Redirect standard input from a file.
 * @cmd: Pointer to the command structure.
 * @status: Pointer to the status variable.
 * Return: 0 on success, -1 on failure.
 */
int stdin_from_file(command *cmd, int *status)
{

	if (access((*cmd).file_for_redir, F_OK) == -1)
	{
		fprintf(stderr, "./hsh: 1: cannot open %s: No such file\n",
				(*cmd).file_for_redir);
		*status = 2;
		return (-1);
	}

	if (access((*cmd).file_for_redir, R_OK) == -1)
	{
		fprintf(stderr, "%s: stdin: Is a directory\n", (*cmd).args[0]);
		*status = 1;
		return (-1);
	}

	(*cmd).fd = open((*cmd).file_for_redir, O_RDONLY);
	if (dup2((*cmd).fd, STDIN_FILENO) == -1)
	{
		perror("dup2");
		return (-1);
	}
	return (0);
}

/**
 * gen_temp_heredoc_file - Generate a temporary file for here-document content.
 * @cmd: Pointer to the command structure.
 * Return: 0 on success, -1 on failure.
 */
int gen_temp_heredoc_file(command *cmd)
{
	char *line = NULL, *temp_file_path, *delim = (*cmd).file_for_redir;
	size_t len_temp_file_path, len = 0;
	ssize_t n_read = 0;

	len_temp_file_path = _strlen("/tmp/") + _strlen(delim);

	temp_file_path = malloc(len_temp_file_path + 1);

	/* Create a temp file of the name of the delim*/
	sprintf(temp_file_path, "/tmp/%s", delim);

	(*cmd).fd = open(temp_file_path, O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);

	if ((*cmd).fd == -1)
		return (-1);

	while (((n_read = getline(&line, &len, stdin)) != -1) &&
		   /* line contains a \n at the end */
		   (_strncmp(line, delim, _strlen(delim)) != 0))
	{
		write((*cmd).fd, line, n_read);
	}
	free(line);
	free((*cmd).file_for_redir);
	(*cmd).file_for_redir = temp_file_path;
	return (0);
}
