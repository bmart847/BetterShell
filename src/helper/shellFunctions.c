#include "shellFunctions.h"
#include "shared.h"
#include <unistd.h>
#include <strings.h>

extern const key_t SHM_KEY;

// Initializes the shared memory space used to store the working directory
void initWorkingDir(char *filename) {
	sharedMemory *init;
	shm_id = shmget(SHM_KEY, 250 * sizeof(char*), IPC_CREAT | 0666);
	unsigned int i;

	if (shm_id < 0) {
		printf("shmget Error\n");
		exit(1);
	}
	printf("Shared memory initialized!\n");
	init = shmat(shm_id, 0, 0);
	init->wdPath[0] = '/';
	init->wdPath[1] = '\0';
	init->wdSize = 1;

	for (i = 0; filename[i] != '\0'; i++) {
		init->fName[i] = filename[i];
	}
	
	init->fSize = i;

	init->FLC = 19;
	
	shmdt(init);
}

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
	letter = strtok(input, " \t\r\n\a");

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
int cmdLaunch(char *input, char **args) {
	/* Initialize Variables */
	pid_t pid, wpid;
	int stat;
	
	/* Fork Process */
	pid = fork();

	/* Error Handlings */
	if(pid == 0) {
		if(execvp(input, args) == -1) {
			perror("Error_Launching_Process");
		}
		return 1;
	} else if (pid < 0) {
		perror("Error_Launching_Process");
		return 2;
	} else {
		/* Wait for child process to complete */
		do {
			wpid = waitpid(pid, &stat, WUNTRACED);
		} while (!WIFEXITED(stat) && !WIFSIGNALED(stat));

	}

	return 0;
}

/* Determines the command and performs neccessary actiions */
int cmdExecute(char **input) {
	/* Initialize Variables */
	char *leadCmd = input[0];
	int index = 1;

	/* Determine command and take action */
	if(leadCmd == NULL) {
		return 0;
	} else if (strcmp(leadCmd, "cat") == 0) {
		cmdLaunch("bin/cat", input);
	} else if (strcmp(leadCmd, "cd") == 0) {
		cmdLaunch("bin/cd", input);
	} else if (strcmp(leadCmd, "df") == 0) {
		cmdLaunch("bin/df", input);
	} else if (strcmp(leadCmd, "help") == 0) {
        printf("To-Do\n");
	} else if (strcmp(leadCmd, "ls") == 0) {
		cmdLaunch("bin/ls", input);
	} else if (strcmp(leadCmd, "mkdir") == 0) {
		cmdLaunch("bin/mkdir", input);
	} else if (strcmp(leadCmd, "pbs") == 0) {
		cmdLaunch("bin/pbs", input);
	} else if (strcmp(leadCmd, "pfe") == 0) {
		cmdLaunch("bin/pfe", input);
	} else if (strcmp(leadCmd, "pwd") == 0) {
        cmdLaunch("bin/pwd", input);
	} else if (strcmp(leadCmd, "rm") == 0) {
        cmdLaunch("bin/rm", input);
	} else if (strcmp(leadCmd, "rmdir") == 0) {
        cmdLaunch("bin/rmdir", input);
	} else if (strcmp(leadCmd, "touch") == 0) {
        cmdLaunch("bin/touch", input);
	} else if (strcmp(leadCmd, "exit") == 0) {
		printf("Quitting\n");
		return 1;
	} else {
		printf("Command not recognized\n");
	}
	return 0;
}
