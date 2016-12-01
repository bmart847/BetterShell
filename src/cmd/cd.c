/*
	Author: Bryan Martin and Joseph Listro
	Class:  CSI 385 <Section 02>
	Assignment: Semester Project
	Date Assigned: 6 September 2016
	Due Date: 6 December 2016
	
	Description:  Changes the working directory.
	
	Certification of Authenticity:
	I certify that this assignment is entirely my own work.
*/

#include <stdio.h>
#include <stdlib.h>

#include "../helper/fatSupport.h"
#include "../helper/fat.h"
#include "../helper/workingDirectory.h"

FILE* FILE_SYSTEM_ID;

int cd_help();

int main(int argc, char *argv[])
{
	// Just a stub
	printf("CD has been called\n");
	
	if (initWorkingDir() != 0)
	{
		return -1;
	}
	
	if (argc == 1)
	{
		// CD to the root directory
	}
	else if (argc == 2)
	{
		// CD to the given path name
	}
	else
	{
		// Too many args
		cd_help();
	}
	return 0;
}

int cd_help() {
	printf("Help for cd command will go here.\n");
	return(0);
}