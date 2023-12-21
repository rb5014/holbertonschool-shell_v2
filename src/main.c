#include "main.h"
/**
 * free_loop - free the strings of a pointer of strings
 * @args: input
 * @nb_args: number of args to free
 * Return: nothing
 */
void free_loop(char **args, int nb_args)
{
	int i;
	for (i = 0; i < nb_args; i++)
	{
		free(args[i]);
		args[i] = NULL;
	}
	free(args);
}
/**
 * fork_wait_execve - creates a child process, exec a command, then leave
 * @p: func
 * @status: error status
 * Return: nothing
 */
void fork_wait_execve(char **p, int *status)
{
	pid_t child = 0;
	int wstatus;

	child = fork();
	if (child == 0)
	{
		if (execve(p[0], p, environ) == -1)
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
/**
 * SIGINT_handler - do nothing
 * @signum: signal number
 */
void SIGINT_handler(int signum)
{
	(void)signum;
}

/**
 * populate_args - fill the args array by separating each args of the line read
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
 * do_cmd - try to execute the command
*/
void do_cmd(char *prog_name, int *status, char **args,
			int nb_args, int *exit_flag)
{
	int builtin_flag = 0;

	builtin_flag = is_builtin(prog_name, args, nb_args, status);
	if (builtin_flag == 0)
	{
		if ((_which(prog_name, args, status) == 0))
			fork_wait_execve(args, status);
	}
	else if (builtin_flag == -1)
		*exit_flag = builtin_flag;
}
/**
 * process_line - parses the line and execute its command
*/
void process_line(char *prog_name, int *status, char *line, int *exit_flag)
{
	char **args = NULL;
	int nb_args;

	nb_args = populate_args(line, &args);
	if (nb_args > 0)
		do_cmd(prog_name, status, args, nb_args, exit_flag);
	free_loop(args, nb_args);
}

/**
 * read_lines - loop over stdin lines and process each of them
 *
*/
void read_lines(char *prog_name, int *status)
{
	int exit_flag = 0;
	size_t len = 0;
	ssize_t nread;
	char *line = NULL;

	while ((exit_flag == 0) &&
		   ((nread = getline(&line, &len, stdin)) != -1))
	{
		process_line(prog_name, status, line, &exit_flag);
	}
	free(line);
}


/**
 * main - creates a shell
 * @argc: number of args
 * @argv: array of arg strings
 * Return: Always 0
 */
int main(int argc, char *argv[])
{
	char *prog_name = NULL;
	int status = 0;

	if (argc)
		prog_name = _strdup(argv[0]);
	signal(SIGINT, SIGINT_handler);

	read_lines(prog_name, &status);

	free(prog_name);
	exit(status);
}
