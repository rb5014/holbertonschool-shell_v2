#include "main.h"

command *resize_cmd_list(command *cmd_list, int *old_size)
{
	int new_size = (*old_size) + 1;
	command *new_cmd_list = _realloc(cmd_list,
	 								 sizeof(command) * (*old_size),
									 sizeof(command) * new_size);
	if (new_cmd_list == NULL)
	{
        perror("Failed to reallocate memory");
        exit(EXIT_FAILURE);
	}
	*old_size = new_size;

	return (new_cmd_list);
}

void add_new_cmd(command **cmd_list, int *nb_cmds, char **args, int nb_args, operator op, char *file_for_redir)
{
    *cmd_list = resize_cmd_list(*cmd_list, nb_cmds);

    (*cmd_list)[*nb_cmds - 1].args = args;
	(*cmd_list)[*nb_cmds - 1].nb_args = nb_args;
	(*cmd_list)[*nb_cmds - 1].op = op;
    if (file_for_redir != NULL) {
        (*cmd_list)[*nb_cmds - 1].file_for_redir = file_for_redir;
    }

}


