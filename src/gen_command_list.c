#include "main.h"

int gen_command_list(command **cmd_list, char **args, int nb_args)
{
	int i = 0;
	int nb_cmds = 0;
	char **current_cmd = NULL;
	int nb_args_current_cmd = 0;
	char *file_for_redir = NULL;
	int is_part_of_pipe = 0, prev_was_pipe = 0;
	position_in_pipe pos_in_pipe = PIPE_NONE;

	operator op = NONE;

	/* The order is very important, because otherwise _strstr will find the wrong substring */
	/* For example if it checks ">" before ">>", the result will succeed even if op is ">>" */
	op_str_to_enum_value conv[] = {{">>", TO_FILE_APPEND}, {">", TO_FILE},
	{"<<", HERE_DOCUMENT}, {"<", FROM_FILE}, {NULL, NONE}};

	for (i = 0; i < nb_args; i++)
	{
		int j;
		if (prev_was_pipe)
		{
			is_part_of_pipe = 1;
			pos_in_pipe = PIPE_END;
		}
		if (_strcmp(args[i], "|") == 0)
		{
			is_part_of_pipe = 1;
			if (prev_was_pipe)
				pos_in_pipe = PIPE_MIDDLE;
			else
				pos_in_pipe = PIPE_START;
			add_new_command(cmd_list, &nb_cmds, current_cmd, nb_args_current_cmd, op, file_for_redir, is_part_of_pipe, pos_in_pipe);
			current_cmd = NULL;
			nb_args_current_cmd = 0;
			op = NONE; /* Reset operator for following cmd */
			prev_was_pipe = 1;
		}
		else
		{
			for (j = 0; conv[j].op_str != NULL; j++)
			{
				if (_strcmp(args[i], conv[j].op_str) == 0)
				{
					op = conv[j].op_enum_value;
					if ((i + 1) < nb_args)
					{
						i++;
						file_for_redir = _strdup(args[i]);
					}
					break;
				}
			}
			if (conv[j].op_str == NULL) /* If no op was found in this current iteration of the args loop */
			{
				add_new_arg(&current_cmd, args[i], &nb_args_current_cmd);
			}

		}

	}
	/* Add last command (or the only command in the line) */
	if (nb_args > 0)
		add_new_command(cmd_list, &nb_cmds, current_cmd, nb_args_current_cmd, op, file_for_redir, is_part_of_pipe, pos_in_pipe);

	return (nb_cmds);
}

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

void add_new_command(command **cmd_list, int *nb_cmds, char **args, int nb_args, operator op, char *file_for_redir, int is_part_of_pipe, position_in_pipe pos_in_pipe)
{
	*cmd_list = resize_cmd_list(*cmd_list, nb_cmds);

	(*cmd_list)[*nb_cmds - 1].args = args;
	(*cmd_list)[*nb_cmds - 1].nb_args = nb_args;
	(*cmd_list)[*nb_cmds - 1].op = op;
	if (file_for_redir != NULL)
		(*cmd_list)[*nb_cmds - 1].file_for_redir = file_for_redir;
	else
		(*cmd_list)[*nb_cmds - 1].file_for_redir = _strdup("");

	(*cmd_list)[*nb_cmds - 1].fd = -1;

	if (is_part_of_pipe == 1)
		pipe((*cmd_list)[*nb_cmds - 1].pipe_fd);
	else
	{
		(*cmd_list)[*nb_cmds - 1].pipe_fd[0] = -1;
		(*cmd_list)[*nb_cmds - 1].pipe_fd[1] = -1;
	}

	(*cmd_list)[*nb_cmds - 1].is_part_of_pipe = is_part_of_pipe;
	(*cmd_list)[*nb_cmds - 1].pos_in_pipe = pos_in_pipe;
	
}


