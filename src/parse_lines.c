#include "main.h"

char **resize_arg_list(char **arg_list, int *old_size)
{
	int new_size = (*old_size) + 1;
	char **new_arg_list = _realloc(arg_list,
									 sizeof(char *) * (*old_size),
									 sizeof(char *) * (new_size + 1));
	if (new_arg_list == NULL)
	{
		perror("Failed to reallocate memory");
		exit(EXIT_FAILURE);
	}
	*old_size = new_size;

	return (new_arg_list);
}

void add_new_arg(char ***arg_list, char *arg, int *nb_args)
{
	if ((arg == NULL) || (_strlen(arg) == 0))
		return;
	*arg_list = resize_arg_list(*arg_list, nb_args);

	(*arg_list)[*nb_args - 1] = _strdup(arg);
	(*arg_list)[*nb_args] = NULL; /* Terminate the array */
}

/*
 * populate_args - Splits a line into arguments based on whitespace
 * and operators
 * @line: The line to be split
 * @args: Pointer to an array of strings where the arguments are stored
 *
 * Return: The number of arguments added to args
 */
int populate_args(char *line, char ***args)
{
	char *delim = " \n", *linetoNULL = line, *token = NULL;
	int nb_args = 0;
	char *operators[] = {">>", ">", "<<", "<", "|", ";", "&&", "||", NULL};
	char **separated_token = NULL;
	int nb_sep_token = 0, i, j;

	while (1)
	{
		token = strtok(linetoNULL, delim);
		if (token == NULL)
			break;
		linetoNULL = NULL;

		for (i = 0; operators[i] != NULL; i++)
		{
			nb_sep_token = 0;
			separated_token = split_token_with_delim(token, operators[i], &nb_sep_token);
			for (j = 0; j < nb_sep_token; j++)
			{
				add_new_arg(args, separated_token[j], &nb_args);
				free(separated_token[j]);
			}
			if (separated_token)
				free(separated_token); /* Free the array of separated tokens */
			if (nb_sep_token > 0)
				break; /* Found and processed an operator */
		}

		if (nb_sep_token == 0)
		{
			add_new_arg(args, token, &nb_args);
		}
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
	int nb_args = 0, nb_cmds = 0;

	command *cmd_list = NULL;

	nb_args = populate_args(line, &args);

	nb_cmds = gen_command_list(&cmd_list, args, nb_args);
	free_loop(args, nb_args);

	execute_command_list(nb_cmds, cmd_list, prog_name, env, status, exit_flag);

	free_commands(&cmd_list, nb_cmds);
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
