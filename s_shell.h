#ifndef S_SHELL_H
#define S_SHELL_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

extern char **environ;
void run(char **ac, char **av, char *buffer);

#endif
