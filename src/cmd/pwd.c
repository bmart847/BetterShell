/*
	Author: Bryan Martin and Joseph Listro
	Class:  CSI 385 <Section 02>
	Assignment: Semester Project
	Date Assigned: 6 September 2016
	Due Date: 6 December 2016
	
	Description:  Prints the current working directory.
	
	Certification of Authenticity:
	I certify that this assignment is entirely my own work.
*/

#include <stdio.h>
#include <stdlib.h>

#include "../helper/fatSupport.h"
#include "../helper/fat.h"
#include "../helper/shared.h"

FILE* FILE_SYSTEM_ID;

int pwd_help();

int main(int argc, char *argv[])
{
	shm_id = shmget(1234, 250 * sizeof(char*), 0666);
	printf("%s\n", dirGet());
	return 0;
}

int pwd_help() {
	printf("Help for pwd command will go here.\n");
	return(0);
}