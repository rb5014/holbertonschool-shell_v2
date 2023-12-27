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
#include "custom_std_functions/custom_std_functions.h"

int is_builtin(char *prog_name, char ***env, char **args,
			   int nb_args, int *status);
void do_env(char **env);
void do_exit(char *prog_name, char **args, int nb_args, int *status);
void print_error_message(char *prog_name, char *cmd, char *arg, int status);
int do_cd(char *prog_name, char ***env, char **args, int nb_args, int *status);
char *determine_new_directory(char *prog_name, char **args, int nb_args,
							  char ***env, int *status);
int change_directory(char *prog_name, char **args, char *new_dir,
					 char *cur_dir, char ***env, int *status);

void free_env(char **env);
char **copy_envp(char *original_envp[]);

void read_lines(char *prog_name, char ***env, int *status);
void process_line(char *prog_name, char ***env, int *status,
				  char *line, int *exit_flag);
int populate_args(char *line, char ***args);
void do_cmd(char *prog_name, char ***env, int *status, char **args,
			int nb_args, int *exit_flag);
int _which(char *prog_name, char **env, char **args, int *status);
void fork_wait_execve(char ***env, char **p, int *status);
void free_loop(char **args, int nb_args);
void SIGINT_handler(int signum);
#endif
