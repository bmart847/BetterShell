/*
	Author: Bryan Martin and Joseph Listro
	Class:  CSI 385 <Section 02>
	Assignment: Semester Project
	Date Assigned: 6 September 2016
	Due Date: 6 December 2016
	
	Description:  Removes the specified directory.
	
	Certification of Authenticity:
	I certify that this assignment is entirely my own work.
*/

#include <stdio.h>
#include <stdlib.h>

#include "../helper/fatSupport.h"
#include "../helper/fat.h"
#include "../helper/workingDirectory.h"

FILE* FILE_SYSTEM_ID;

int rmdir_help();

int main(int argc, char *argv[])
{
	// Just a stub
	printf("rmdir has been called\n");
	return 0;
}

int rmdir_help()
{
	printf("Help for rmdir command will go here.\n");
	return(0);
}