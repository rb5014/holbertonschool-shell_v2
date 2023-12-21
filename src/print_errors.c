#include "main.h"

/**
* print_error_message - print the error message corresponding to the status
* @prog_name: name of the program
* @cmd: name of the command used (exit, ls, etc)
* @arg: arg of the command
* @status: status associated with the error
*/
void print_error_message(char *prog_name, char *cmd, char *arg, int status)
{
	switch (status)
	{
		case 2:
		case 232:
			fprintf(stderr, "%s: 1: %s: Illegal number: %s\n", prog_name, cmd, arg);
			break;

		case 127:
			fprintf(stderr, "%s: 1: %s: not found\n", prog_name, cmd);
			break;

		default:
			break;
	}
}
