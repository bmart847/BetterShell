#include "shellFunctions.h"


/* Obtains input from the user */
char *get_line(){
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
char **parseInput(char *input){
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
