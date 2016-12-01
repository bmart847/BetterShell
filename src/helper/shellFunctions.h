/*
	Author: Bryan Martin and Joseph Listro
	Class:  CSI 385 <Section 02>
	Assignment: Semester Project
	Date Assigned: 6 September 2016
	Due Date: 6 December 2016
	
	Description:  Provides function for the parent process to access shared
	memory and manage input from the user.
	
	Certification of Authenticity:
	I certify that this assignment is entirely my own work.
*/

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <unistd.h>

#ifndef SHELLFUNCTIONS_H
#define SHELLFUNCTIONS_H

void initWorkingDir();
char *get_line();
char **parseInput(char *input);
int cmdLaunch(char *input);
int cmdExecute(char **input);

extern char* WORKING_DIRECTORY;


#endif
