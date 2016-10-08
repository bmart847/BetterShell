#include "shellFunctions.h"

/* Main Function (Currently Just Runs Shell) */
int main(int argc, char *argv[]) {
	char *input;
	char **cmd;
	int status;

	do {
		printf("> ");
		input = get_line();
		cmd = parseInput(input);
		status = cmdExecute(cmd);
		free(input);
		free(cmd);
	} while (status);
}
