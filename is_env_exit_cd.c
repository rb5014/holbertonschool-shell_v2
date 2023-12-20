#include "main.h"
/**
 * is_env - prints environment variables if env found
 * @arg: arg to check
 * Return: 0 if found, -1 if not or error
 */

int is_env(char *arg)
{
	if (arg && strcmp(arg, "env") == 0)
	{
		printenv();
		return (0);
	}
	return (-1);
}

/**
 * is_exit - if exit found, free arg and return 0
 * @arg: arg to check if it is "exit"
 * Return: 1 if found, 0 if not
 */
int is_exit(char *arg)
{
	if (strcmp(arg, "exit") == 0)
		return (1);
	return (0);
}

/**
 * is_cd - if cd found, change the current working directory
 * @arg: arg to check if it is cd
 * Return: 1 if found, 0 if not
 */
int is_cd(char *arg)
{
	if (strcmp(arg, "exit") == 0)
		return (1);
	return (0);
}
