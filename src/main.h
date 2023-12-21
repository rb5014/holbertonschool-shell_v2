#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <signal.h>
#include "custom_functions/custom_functions.h"

int is_env(char *arg);
int is_exit(char *prog_name, char **args, int nb_args, int *status);
void print_error_message(char *prog_name, char *cmd, char *arg, int status);
int is_cd(char *arg);
int _which(char *prog_name, char **args, int *status);
void fork_wait_execve(char **p, int *status);
void free_loop(char **args, int nb_args);
void printenv(void);
void SIGINT_handler(int signum);
#endif
