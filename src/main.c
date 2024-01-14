#include "main.h"

/**
 * main - Entry point for a custom shell program.
 * @argc: The count of arguments passed to the program.
 * @argv: Array of arguments passed to the program.
 * @envp: Array of environment variables.
 * Description: Initializes the program, sets up signal handling,
 * reads and processes lines from stdin, and cleans up before exiting.
 * Return: Returns 0 upon successful completion.
 */
int main(int argc, char *argv[], char *envp[])
{
	char **hsh_env = copy_envp(envp);
	char *prog_name = NULL;
	int status = 0;

	if (argc)
		prog_name = _strdup(argv[0]);
	signal(SIGINT, SIGINT_handler);

	read_lines(prog_name, &hsh_env, &status);

	free(prog_name);
	free_env(hsh_env);
	exit(status);
}
