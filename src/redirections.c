#include "main.h"

int do_redirection(operator op, char *file_for_redir, char *cmd_name, int *status)
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

		case HERE_DOCUMENT:
			file_for_redir = gen_temp_heredoc_file(file_for_redir);
		case FROM_FILE:
			std_fd_save = dup(STDIN_FILENO);
			if (stdin_from_file(file_for_redir, cmd_name, status) == -1)
				return (-1);
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
		case FROM_FILE:
		case HERE_DOCUMENT:
			if (dup2(std_fd_save, STDIN_FILENO) == -1)
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

int stdin_from_file(char *file_for_redir, char *cmd_name, int *status)
{
	int fd;

	if (access(file_for_redir, F_OK) == -1)
	{
		fprintf(stderr, "./hsh: 1: cannot open %s: No such file\n", file_for_redir);
		*status = 2;
		return (-1);
	}

	if (access(file_for_redir, R_OK) == -1)
	{
		fprintf(stderr, "%s: stdin: Is a directory\n", cmd_name);
		*status = 1;
		return (-1);
	}

	fd = open(file_for_redir, O_RDONLY);
	if (dup2(fd, STDIN_FILENO) == -1)
	{
		perror("dup2");
		return (-1);
	}
	close(fd);
	return (fd);
}

char *gen_temp_heredoc_file(char *here_doc_delim)
{
	char *temp_file = NULL;
	int fd;
	char *line;
	size_t len = 0;
	ssize_t n_read;

	/* Create a temp file of the name of the delim*/
	sprintf(temp_file, "/tmp/%s", here_doc_delim);

	fd = open(temp_file, O_CREAT | O_WRONLY | O_APPEND, S_IRWXU);
	
	while (_strcmp(line, here_doc_delim) != 0)
	{
		n_read = getline(&line, &len, stdin);
		write(fd, line, n_read);
	}

	return (temp_file);
}
