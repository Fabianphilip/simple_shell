#ifndef S_SHELL_H
#define S_SHELL_H

#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>

#define MAX_ARGUMENTS 10

void exec(char *argv[], char **argument);
char **parse_arguments(char *input);

#endif
