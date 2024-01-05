#include "main.h"

int do_redirection(operator op, char *file_for_redir)
{
	int std_fd_save = -1;

	switch (op)
	{
		case TO_FILE:
			std_fd_save = dup(STDOUT_FILENO);
			stdout_to_file(file_for_redir, 0);
			break;

		case TO_FILE_APPEND:
			std_fd_save = dup(STDOUT_FILENO);
			stdout_to_file(file_for_redir, 1);
			break;

		case FROM_FILE:
			std_fd_save = dup(STDIN_FILENO);
			stdin_from_file(file_for_redir);
			break;

		default:
			break;
	}
	return (std_fd_save);
}

void do_revert_redirection(operator op, int std_fd_save)
{
	switch (op)
	{
		case TO_FILE:
		case TO_FILE_APPEND:
			if (dup2(std_fd_save, STDOUT_FILENO) == -1)
			{
				perror("dup2");
			}
			break;
		default:
			break;
	}
}

int stdout_to_file(char *file_for_redir, int is_append)
{
	int fd;

	if ((is_append != 0))
		fd = open(file_for_redir, O_CREAT | O_WRONLY | O_APPEND, S_IRWXU);
	else
		fd = open(file_for_redir, O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		perror("dup2");
		return (-1);
	}
	close(fd);
	return (fd);
}

int stdin_from_file(char *file_for_redir)
{
	int fd;

	fd = open(file_for_redir, O_CREAT | O_RDONLY);
	if (dup2(fd, STDIN_FILENO) == -1)
	{
		perror("dup2");
		return (-1);
	}
	close(fd);
	return (fd);
}