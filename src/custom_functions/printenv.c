#include "custom_functions.h"
/**
 * printenv - print all environment variables and their content
 */
void printenv(void)
{
	int i = 0;

	while (environ[i] != NULL)
	{
		printf("%s\n", environ[i]);
		i++;
	}
}
