/*
	Author: Bryan Martin and Joseph Listro
	Class:  CSI 385 <Section 02>
	Assignment: Semester Project
	Date Assigned: 6 September 2016
	Due Date: 6 December 2016
	
	Description:  print the number of free logical blocks *DISK FREE*.
	
	Certification of Authenticity:
	I certify that this assignment is entirely my own work.
*/

#include <stdio.h>
#include <stdlib.h>

#include "../helper/fatSupport.h"
#include "../helper/fat.h"
#include "../helper/workingDirectory.h"

FILE* FILE_SYSTEM_ID;

int df_help();

int main(int argc, char *argv[])
{
	// Just a stub
	printf("df has been called\n");
	return 0;
}

int df_help() {
	printf("Help for df command will go here.\n");
	return(0);
}