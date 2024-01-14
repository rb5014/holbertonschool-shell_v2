#include "main.h"

/**
 * print_error_message - Prints the error message corresponding
 * to a given status.
 * @prog_name: Name of the program.
 * @cmd: Name of the command that caused the error (e.g., 'exit', 'ls').
 * @arg: Argument of the command that caused the error.
 * @status: Status code associated with the error.
 * Description: Depending on the status code, prints
 * an appropriate error message
 * to the standard error stream. Handles different error cases, such as illegal
 * numbers, command not found, and directory change failures.
 */
void print_error_message(char *prog_name, char *cmd, char *arg, int status)
{
	switch (status)
	{
		case 0:
			fprintf(stderr, "%s: 1: %s: can't cd to %s\n", prog_name, cmd, arg);
			break;

		case 1:
			fprintf(stderr, "%s: %s: %s not set\n", prog_name, cmd, arg);
			break;

		case 2:
			fprintf(stderr, "%s: 1: %s: Illegal number: %s\n", prog_name, cmd, arg);
			break;

		case 127:
			fprintf(stderr, "%s: 1: %s: not found\n", prog_name, cmd);
			break;

		default:
			break;
	}
}

/**
 * print_cmd_struct - Prints the contents of a command structure.
 * @cmd: The command structure to be printed.
 */
void print_cmd_struct(command cmd)
{
	int i;

	printf("args:");
	for (i = 0; i < cmd.nb_args; i++)
	{
		printf(" %s", cmd.args[i]);
	}
	puts("");
	printf("nb_args: %i\n", cmd.nb_args);
	printf("file_op: %i\n", cmd.file_op);
	printf("logical_op: %i\n", cmd.logical_op);
	if (cmd.file_for_redir)
		printf("file_for_redir: %s\n", cmd.file_for_redir);
	else
		printf("file_for_redir: ");
	printf("fd: %i\n", cmd.fd);
	printf("pipe_op: %i\n", cmd.pipe_op);
	printf("pipe_fd[0]: %i\n", cmd.pipe_fd[0]);
	printf("pipe_fd[1]: %i\n", cmd.pipe_fd[1]);
	printf("pos_in_pipe: %i\n", cmd.pos_in_pipe);
	puts("");
}
