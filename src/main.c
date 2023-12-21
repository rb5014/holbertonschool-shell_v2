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
		wait(&(*status));
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
 * main - creates a shell
 * @argc: number of args
 * @argv: array of arg strings
 * Return: Always 0
 */
int main(int argc, char *argv[])
{
	size_t len = 0;
	char **args = NULL;
	ssize_t nread;
	char *delim = " \n", *line = NULL, *linetoNULL, *token = NULL, *prog_name;
	int status = 0, nb_args = 0, exit_flag = 0;

	if (argc)
		prog_name = strdup(argv[0]);
	signal(SIGINT, SIGINT_handler);

	while ((exit_flag == 0) &&
		   ((nread = getline(&line, &len, stdin)) != -1))
	{
		nb_args = 0;
		linetoNULL = line;
		while (1)
		{
			token = strtok(linetoNULL, delim);
			if (token == NULL)
				break;
			linetoNULL = NULL;
			nb_args++;
			/*add + 1 in realloc to add a NULL pointer at the end of the array */
			args = _realloc(args, sizeof(char *) * (nb_args),
						    sizeof(char *) * (nb_args + 1));
			args[nb_args - 1] = _strdup(token);
			args[nb_args] = NULL; /* Terminate the array */
		}
		if (nb_args > 0)
		{
			exit_flag = is_exit(prog_name, args, nb_args, &status);
			if ((exit_flag == 0) && (_which(prog_name, args, &status) == 0))
				fork_wait_execve(args, &status);
		}
		free_loop(args, nb_args);
	}
	free(args);
	free(line);
	free(prog_name);
	exit(status);
}
