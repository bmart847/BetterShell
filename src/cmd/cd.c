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
#include "../helper/shared.h"

FILE* FILE_SYSTEM_ID;

int cd_help();

int main(int argc, char *argv[])
{
	printf("CD has been called\n");
	
	// TODO: Add access to shared memory
	
	if (argc == 1)
	{
		// Change the working directory to root
		dirSet("/");
		filenameSet("");
		flcSet(0);
		
		// Set sharedMemory (working directory) to root
		dirRe(&root);
	}
	else if (argc == 2)
	{
		// CD to the given path name
		enterDirectory(dirGet(), argv[1])
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