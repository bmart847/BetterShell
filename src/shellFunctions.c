#include "shellFunctions.h"


/* Obtains input from the user */
char *get_line() {
	/* Initialize Variables */
	char *input = NULL;
	ssize_t bufsize = 0;

	/* Get the line */
	if (getline(&input, &bufsize, stdin) == -1){
		perror("Error_Getting_Line");
	}

	/* Return the char array */
	return input;
}

/* Parses the user input */
char **parseInput(char *input) {
	/* Initialize Variables */
	int pos = 0;
	char **letters = malloc(128);
	char *letter;

	/* Traverse Input */
	letter = strtok(line, " \t\r\n\a");

	while(letter != NULL) {
		letters[pos] = letter;
		pos ++;
		letter = strtok(NULL, " \t\r\n\a");
	}

	/* Add Null Terminator */
	letters[pos] = NULL;

	/* Return array of char arrays */
	return letters;
}

/* Forks a process for the given command */
int cmdLaunch(char **input) {
	/* Initialize Variables */
	pid_t pid, wpid;
	int stat;

	/* Fork Process */
	pid = fork();

	/* Error Handling */
	if(pid == 0) {
		if(execvp(input[0], input) == -1) {
			perror("Error_Launching_Process");
		}
		return 1;
	} else if (pid < 0) {
		perror("Error_Launching_Process");
		return 2;
	} else {

	}

	return 0;
}

/* Determines the command and performs neccessary actiions */
int cmdExecute(char **input) {
	/* Initialize Variables */
	char *leadCmd = input[0];	

	if(leadCmd == NULL) {
		return 0;
	} else if (strcmp(leadCmd, "cat") == 0) {
		printf("Command not yet implemented");
	} else if (strcmp(leadCmd, "cd") == 0) {
                printf("Command not yet implemented");
	} else if (strcmp(leadCmd, "df") == 0) {
                printf("Command not yet implemented");
	} else if (strcmp(leadCmd, "ls") == 0) {
                printf("Command not yet implemented");
	} else if (strcmp(leadCmd, "mkdir") == 0) {
                printf("Command not yet implemented");
	} else if (strcmp(leadCmd, "pbs") == 0) {
                printf("Command not yet implemented");
	} else if (strcmp(leadCmd, "pfe") == 0) {
                printf("Command not yet implemented");
	} else if (strcmp(leadCmd, "pwd") == 0) {
                printf("Command not yet implemented");
	} else if (strcmp(leadCmd, "rm") == 0) {
                printf("Command not yet implemented");	
	} else if (strcmp(leadCmd, "rmdir") == 0) {
                printf("Command not yet implemented");
	} else if (strcmp(leadCmd, "touch") == 0) {
                printf("Command not yet implemented");
	} else {
		printf("Command not recognized");
	}
	return 0;
}
