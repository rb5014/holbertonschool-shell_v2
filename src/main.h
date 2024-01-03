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

#include "custom_std_functions/custom_std_functions.h"

typedef enum
{
	TO_FILE,
	TO_FILE_APPEND,
	FROM_FILE,
	HERE_DOCUMENT,
	PIPE,
	NONE
} operator;

typedef struct
{
	char *op_str;
	operator op_enum_value;
} op_str_to_enum_value;

typedef struct
{
	char **args;
	int nb_args;
	operator op;
	char *file_for_redir;
} command;

int is_builtin(char *prog_name, char ***env, char **args,
			   int nb_args, int *status);
void do_env(char **env);
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
void add_new_arg(char ***arg_list, char *arg, int *nb_args);
char **resize_arg_list(char **arg_list, int *old_size);

int gen_command_list(command **cmd_list, char **args, int nb_args);
command *resize_cmd_list(command *cmd_list, int *old_size);
void add_new_command(command **cmd_list, int *nb_cmds, char **args, int nb_args, operator op, char *file_for_redir);

void do_cmd(char *prog_name, char ***env, int *status, command cmd, int *exit_flag);
int _which(char *prog_name, char **env, char **args, int *status);
void fork_wait_execve(char ***env, char **p, int *status);
void free_loop(char **args, int nb_args);
void SIGINT_handler(int signum);

int do_redirection(operator op, char *file_for_redir);
void do_revert_redirection(operator op, int std_fd_save);
int stdout_to_file(char *file_for_redir, int is_append);
#endif
