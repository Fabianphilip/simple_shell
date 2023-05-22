#ifndef S_SHELL_H
#define S_SHELL_H

#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>

void exec(char *argv[], char *arg[]);

#endif
