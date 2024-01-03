#include "main.h"


/**
 * populate_args - Splits a string into an array of arguments.
 * @line: String to be split.
 * @args: Pointer to an array of strings for storing arguments.
 * Description: Tokenizes 'line' using space and newline as delimiters.
 * Each token is dynamically allocated and added to 'args', which is
 * resized as needed. Ensures the array is NULL-terminated.
 * Return: Total number of arguments stored in 'args'.
 */

int populate_args(char *line, char ***args)
{
	char *delim = " \n", *linetoNULL = line, *token = NULL;
	int nb_args = 0;

	while (1)
	{
		token = strtok(linetoNULL, delim);
		if (token == NULL)
			break;
		linetoNULL = NULL;
		nb_args++;
		/*add + 1 in realloc to add a NULL pointer at the end of the array */
		*args = _realloc(*args, sizeof(char *) * (nb_args),
						sizeof(char *) * (nb_args + 1));
		(*args)[nb_args - 1] = _strdup(token);
		(*args)[nb_args] = NULL; /* Terminate the array */
	}
	return (nb_args);
}

/**
 * process_line - Parses a line of input and executes its command.
 * @prog_name: The name of the program.
 * @env: Pointer to the environment variables.
 * @status: Pointer to an int to store the status of the command execution.
 * @line: The line of input to process.
 * @exit_flag: Pointer to an int that signals if the program should exit.
 * Description: Splits the line into arguments,
 * executes the command in the line,
 * and frees the allocated memory for arguments.
 */
void process_line(char *prog_name, char ***env, int *status,
				  char *line, int *exit_flag)
{
	char **args = NULL;
	int nb_args, nb_cmds, i;

	command *cmd_list = NULL;

	nb_args = populate_args(line, &args);

	nb_cmds = gen_command_list(&cmd_list, args, nb_args);

	for (i = 0; i < nb_cmds; i++)
	{
		if (cmd_list[i].nb_args > 0)
		{
			do_cmd(prog_name, env, status, cmd_list[i], exit_flag);
			free_loop(cmd_list[i].args, cmd_list[i].nb_args);
		}
	}
	free(cmd_list);
	free_loop(args, nb_args);
}

/**
 * read_lines - Reads lines from stdin and processes each line.
 * @prog_name: The name of the program.
 * @env: Pointer to the environment variables.
 * @status: Pointer to an int to store the status of the command execution.
 * Description: Continuously reads lines from standard input,
 * processes each line by executing its command,
 * and stops if an exit signal is received or EOF is reached.
 */
void read_lines(char *prog_name, char ***env, int *status)
{
	int exit_flag = 0;
	size_t len = 0;
	ssize_t nread;
	char *line = NULL;

	while ((exit_flag == 0) &&
		   ((nread = getline(&line, &len, stdin)) != -1))
	{
		process_line(prog_name, env, status, line, &exit_flag);
	}
	free(line);
}
