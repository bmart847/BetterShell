#include <errno.h>
#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

char *get_line();
char **parseInput(char *input);
int cmdLaunch(char **input);
int cmdExecute(char **input);
