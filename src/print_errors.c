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
