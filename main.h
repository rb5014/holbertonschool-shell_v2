#ifndef MAIN_H
#define MAIN_H
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <signal.h>
extern char **environ;
int is_env(char *arg);
int is_exit(char *arg);
int is_cd(char *arg);
int _which(char **args, int *status);
void fork_wait_execve(char **p, int *status);
void free_loop(char **args, int nb_args);
void printenv(void);
void SIGINT_handler(int signum);
#endif
