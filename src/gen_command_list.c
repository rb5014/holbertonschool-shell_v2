#include "main.h"

/**
 * gen_command_list - Generates a list of command structures
*					  based on the input arguments.
 * @cmd_list: Pointer to the command list.
 * @args: Array of input arguments.
 * @nb_args: Number of input arguments.
 * Return: Number of commands generated.
 */
int gen_command_list(command **cmd_list, char **args, int nb_args)
{
	int i, nb_cmds = 0;
	command current_cmd = generate_new_command_struct();

	if (nb_args == 0)
		return (0);

	for (i = 0; i < nb_args; i++)
	{
		operator op = is_operator(args[i]);

		if (op == NONE)
			add_new_arg(&current_cmd.args, args[i], &current_cmd.nb_args);
		else if ((op == PIPE) || (op == AND) || (op == OR) || (op == SEMICOLON))
		{
			add_new_command(cmd_list, &nb_cmds, current_cmd, op);
			current_cmd = generate_new_command_struct();
			if (op == PIPE)
			{
				current_cmd.pipe_op = PIPE;
				current_cmd.pos_in_pipe = PIPE_END;
			}
		}
		else if ((op == TO_FILE) || (op == TO_FILE_APPEND)
				 || (op == FROM_FILE) || (op == HERE_DOCUMENT))
		{
			current_cmd.file_op = op;
			if ((i + 1) < nb_args)
			{
				i++;
				current_cmd.file_for_redir = _strdup(args[i]);
			}
		}
	}
	/* Add last command (or the only command in the line) */
	if (current_cmd.nb_args > 0)
		add_new_command(cmd_list, &nb_cmds, current_cmd, NONE);
	return (nb_cmds);
}

/**
 * generate_new_command_struct - Creates a new command
 *								 structure with default values.
 * Return: Newly created command structure.
 */
command generate_new_command_struct(void)
{
	command cmd = {
			NULL,	  /* args */
			0,		  /* nb_args */
			NONE,	  /* file_op */
			NONE,	  /* logical_op */
			NONE,	  /* pipe_op */
			NULL,	  /* file_for_redir */
			-1,		  /* fd */
			{-1, -1}, /* pipe_fd[2] */
			PIPE_NONE /* pos_in_pipe */
		};
	return (cmd);
}

/**
 * is_operator - Checks if a given argument is an operator
 *				 and returns its corresponding enum value.
 * @arg: Input argument to check.
 * Return: Operator enum value.
 */
operator is_operator(char *arg)
{
	op_str_to_enum_value conv[] = {{">>", TO_FILE_APPEND}, {">", TO_FILE},
								   {"<<", HERE_DOCUMENT}, {"<", FROM_FILE},
								   {"&&", AND}, {"||", OR}, {"|", PIPE},
								   {";", SEMICOLON}, {NULL, NONE}};

	int i;

	for (i = 0; conv[i].op_str != NULL; i++)
	{
		if (_strcmp(arg, conv[i].op_str) == 0)
			break;
	}
	return (conv[i].op_enum_value);
}

/**
 * resize_cmd_list - Resizes the command list by allocating additional space.
 * @cmd_list: Pointer to the command list.
 * @old_size: Pointer to the old size of the command list.
 * Return: Pointer to the resized command list.
 */
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

/**
 * add_new_command - Adds a new command to the command list.
 * @cmd_list: Pointer to the command list.
 * @nb_cmds: Pointer to the number of commands.
 * @cmd: Command structure to be added.
 * @op: Operator associated with the command.
 */
void add_new_command(command **cmd_list, int *nb_cmds, command cmd,
					 operator op)
{
	*cmd_list = resize_cmd_list(*cmd_list, nb_cmds);

	if (op == PIPE)
	{
		if (cmd.pipe_op == NONE)
		{
			cmd.pipe_op = PIPE;
			cmd.pos_in_pipe = PIPE_START;
		}
		else if (cmd.pipe_op == PIPE) /* Previously assigned to PIPE_END */
			cmd.pos_in_pipe = PIPE_MIDDLE;
	}
	else if ((op == AND) || (op == OR))
		cmd.logical_op = op;

	/* Separated because for the PIPE_END, param 'op' will not be PIPE */
	/* but cmd.pipe_op assigned to PIPE for next cmd in gen_cmd_list function */
	if (cmd.pipe_op == PIPE)
		pipe(cmd.pipe_fd);

	(*cmd_list)[*nb_cmds - 1] = cmd;
}
