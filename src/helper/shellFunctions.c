#include "shellFunctions.h"

// Initializes the shared memory space used to store the working directory
void initWorkingDir() {
	sharedMemory *init;
	shm_id = shmget(IPC_PRIVATE, 250 * sizeof(char*), IPC_CREAT | 0666);
	if (shm_id < 0) {
		printf("shmget Error\n");
		exit(1);
	}
	printf("Shared memory initialized!\n");
	init = shmat(shm_id, 0, 0);
	init->wdPath[0] = '/';
	init->wdPath[1] = '\0';
	init->wdSize = 1;
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

	/* Determine command and take action */
	if(leadCmd == NULL) {
		return 0;
	} else if (strcmp(leadCmd, "cat") == 0) {
		printf("Command not yet implemented\n");
	} else if (strcmp(leadCmd, "cd") == 0) {
		char *newDir = input[1];
		enterDir(newDir);
                printf("%s\n", WORKING_DIRECTORY);
	} else if (strcmp(leadCmd, "df") == 0) {
                printf("Command not yet implemented\n");
        } else if (strcmp(leadCmd, "help") == 0) {
                printf("Command not yet implemented\n");
	} else if (strcmp(leadCmd, "ls") == 0) {
                printf("Command not yet implemented\n");
	} else if (strcmp(leadCmd, "mkdir") == 0) {
                printf("Command not yet implemented\n");
	} else if (strcmp(leadCmd, "pbs") == 0) {
		if(input[1] == NULL) {
			pbs();
		} else if(strcmp((char*)input[1], "--help") == 0) {
			pbs_help();
		}
	} else if (strcmp(leadCmd, "pfe") == 0) {
		if(input[1] != NULL && input[2] != NULL && input[3] == NULL) {
			pfe(atoi(input[1]), atoi(input[2]));
		} else if((strcmp((char*)input[1], "--help") == 0) && input[2] == NULL) {
			pfe_help();
		} else {
			printf("Invalid parameters.\n");
		}
	} else if (strcmp(leadCmd, "pwd") == 0) {
                printf("%s\n", WORKING_DIRECTORY);
	} else if (strcmp(leadCmd, "rm") == 0) {
                printf("Command not yet implemented\n");	
	} else if (strcmp(leadCmd, "rmdir") == 0) {
                printf("Command not yet implemented\n");
	} else if (strcmp(leadCmd, "touch") == 0) {
                printf("Command not yet implemented\n");
	} else if (strcmp(leadCmd, "exit") == 0) {
		printf("Quitting\n");
		return 1;
	} else {
		printf("Command not recognized\n");
	}
	return 0;
}
