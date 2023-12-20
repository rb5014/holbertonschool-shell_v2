#include "main.h"
/**
 * printenv - print all environment variables and their content
 */
void printenv(void)
{
	int i = 0;

	while (environ[i] != NULL)
	{
		puts(environ[i]);
		i++;
	}
}
