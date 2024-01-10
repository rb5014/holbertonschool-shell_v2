#include "main.h"

/**
 * free_loop - Frees a pointer to an array of strings.
 * @args: Pointer to the array of strings.
 * @nb_args: The number of strings in the array.
 * Description: Iterates through each string in the array, frees it,
 * and sets its pointer to NULL. Finally, frees the array pointer.
 */

void free_loop(char **args, int nb_args)
{
	int i;

	for (i = 0; i < nb_args; i++)
	{
		if (args[i])
			free(args[i]);
		args[i] = NULL;
	}
	free(args);
}

void free_commands(command **cmd_list, int nb_cmds)
{
	int i;

	for (i = 0; i < nb_cmds; i++)
	{
		free_loop((*cmd_list)[i].args, (*cmd_list)[i].nb_args);
		free((*cmd_list)[i].file_for_redir);
	}
	free(*cmd_list);
}