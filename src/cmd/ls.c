/*
	Author: Bryan Martin and Joseph Listro
	Class:  CSI 385 <Section 02>
	Assignment: Semester Project
	Date Assigned: 6 September 2016
	Due Date: 6 December 2016
	
	Description:  Lists the entries in the directory or the file/directory entry contents.
	
	Certification of Authenticity:
	I certify that this assignment is entirely my own work.
*/

#include <stdio.h>
#include <stdlib.h>

#include "../helper/fatSupport.h"
#include "../helper/fat.h"
#include "../helper/shared.h"

FILE* FILE_SYSTEM_ID;

int ls_help();

int main(int argc, char *argv[])
{
	// Just a stub
	printf("ls has been called\n");
	return 0;
}

int ls_help() {
	printf("Help for ls command will go here.\n");
	return(0);
}