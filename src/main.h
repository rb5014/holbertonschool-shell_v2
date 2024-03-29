#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <signal.h>
#include "errno.h"
#include <fcntl.h>
#include <sys/stat.h>

#include "custom_std_functions/custom_std_functions.h"

/**
 * enum operator - Enumerates possible operators for command processing.
 * @NONE: Represents no operation.
 * @TO_FILE: Redirects output to a file.
 * @TO_FILE_APPEND: Redirects and appends output to a file.
 * @FROM_FILE: Redirects input from a file.
 * @HERE_DOCUMENT: Redirects input from a here-document.
 * @PIPE: Pipes output to another command.
 * @AND: Represents the logical AND operator.
 * @OR: Represents the logical OR operator.
 * @SEMICOLON: Serves as a command separator.
 */
typedef enum operator
{
	NONE,
	TO_FILE,
	TO_FILE_APPEND,
	FROM_FILE,
	HERE_DOCUMENT,
	PIPE,
	AND,
	OR,
	SEMICOLON
}
operator;

/**
 * enum position_in_pipe - Enumerates positions within
 * a pipe for command processing.
 * @PIPE_NONE: No pipe operation.
 * @PIPE_START: Start of a pipe.
 * @PIPE_MIDDLE: Middle of a pipe.
 * @PIPE_END: End of a pipe.
 */
typedef enum position_in_pipe
{
	PIPE_NONE,
	PIPE_START,
	PIPE_MIDDLE,
	PIPE_END
} position_in_pipe;

/**
 * struct op_str_to_enum_value - Maps operator strings to
 * their corresponding enum values.
 * @op_str: Operator string.
 * @op_enum_value: Corresponding enum value.
 */
typedef struct op_str_to_enum_value
{
	char *op_str;
	operator op_enum_value;
} op_str_to_enum_value;

/**
 * struct command - Represents a command with associated attributes.
 * @args: Array of arguments.
 * @nb_args: Number of arguments.
 * @file_op: File operation type.
 * @logical_op: Logical operation type.
 * @pipe_op: Pipe operation type.
 * @file_for_redir: File for redirection.
 * @fd: File descriptor.
 * @pipe_fd: Pipe file descriptors.
 * @pos_in_pipe: Position in pipe.
 */
typedef struct command
{
	char **args;
	int nb_args;
	operator file_op;
	operator logical_op;
	operator pipe_op;
	char *file_for_redir;
	int fd;
	int pipe_fd[2];
	position_in_pipe pos_in_pipe;
} command;

int is_builtin(char *prog_name, char ***env, char **args,
			   int nb_args, int *status, int *exit_flag);

void do_env(char **env);
void do_setenv(char ***env, char **args, int nb_args);
void do_unsetenv(char ***env, char **args, int nb_args);

void do_exit(char *prog_name, char **args, int nb_args, int *status);
void print_error_message(char *prog_name, char *cmd, char *arg, int status);
int do_cd(char *prog_name, char ***env, char **args, int nb_args, int *status);
char *determine_new_directory(char **args, int nb_args, char ***env);
int change_directory(char *prog_name, char **args, int nb_args, char *new_dir,
					 char *cur_dir, char ***env, int *status);

void free_env(char **env);
char **copy_envp(char *original_envp[]);

void read_lines(char *prog_name, char ***env, int *status);
void process_line(char *prog_name, char ***env, int *status,
				  char *line, int *exit_flag);
int populate_args(char *line, char ***args);
char **split_token_with_delim(char *token, char *delim, int *nb_args);
void add_new_arg(char ***arg_list, char *arg, int *nb_args);
char **resize_arg_list(char **arg_list, int *old_size);

int gen_command_list(command **cmd_list, char **args, int nb_args);
operator is_operator(char *arg);
command *resize_cmd_list(command *cmd_list, int *old_size);
void add_new_command(command **cmd_list, int *nb_cmds,
					 command cmd, operator op);
command generate_new_command_struct(void);
void print_cmd_struct(command cmd);

char *_which(char *prog_name, char **env, char **args, int *status);
void free_loop(char **args, int nb_args);
void free_commands(command **cmd_list, int nb_cmds);
void SIGINT_handler(int signum);

int do_redirection(command *cmd, int *status);
void do_revert_redirection(command *cmd, int std_fd_save);
int stdout_to_file(command *cmd, int is_append);
int stdin_from_file(command *cmd, int *status);
int gen_temp_heredoc_file(command *cmd);
void execute_command_list(int nb_cmds, command *cmd_list, char *prog_name,
						  char ***env, int *status, int *exit_flag);
void execute_command(command *cmd_list, int i, int nb_cmds, char ***env,
					 char *full_path_cmd);
void close_all_pipes(command *cmd_list, int nb_cmds);
#endif
