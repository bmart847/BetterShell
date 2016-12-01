/*
	Author: Bryan Martin and Joseph Listro
	Class:  CSI 385 <Section 02>
	Assignment: Semester Project
	Date Assigned: 6 September 2016
	Due Date: 6 December 2016

	Description:  These functions were provided to us, minor modifications have
	been made.

	Certification of Authenticity:
	I certify that this assignment is entirely my own work.
*/

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#ifndef FATSUPPORT_H
#define FATSUPPORT_H

int read_sector(int sector_number, unsigned char* buffer);
int write_sector(int sector_number, unsigned char* buffer);

unsigned int get_fat_entry(int fat_entry_number, unsigned char* fat);
void set_fat_entry(int fat_entry_number, int value, unsigned char* fat);

#endif
