/* Chris Bendel, Julien Gilbert */

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char **argv) {
    char *line;    // input pre-parse
    char **input;       // input parsed
    int status;
    
    do
    {
        printf("bettershell --> ");
        line = readInput();
        input = parseInput(line);
        status = cmdExecute(input);
        /* free allocated memory */
        free(line);
	    free(input);
    } while(status == 0);
    
	return EXIT_SUCCESS;
}

/* parses the user input */
char ** parseInput(char *input)
{
    /* Initialize Variables */
    int pos = 0;
    char **letters = malloc(128 * sizeof(char));
    char *letter;
 
    /* Traverse Input */
    letter = strtok(input, " \t\r\n\a");
 
    while(letter != NULL)
    {
        letters[pos] = letter;
        pos ++;
        letter = strtok(NULL, " \t\r\n\a");
    }
 
    /* Add Null Terminator */
    letters[pos] = NULL;
 
    /* Return array of char arrays */
    return letters;
}

/* reads and returns line from user */
char * readInput(void)
{
    char *line = NULL;
    ssize_t bufsize = 0; // allocates a buffer
    printf("bettershell ---> ");
    if (getline(&input, &bufsize, stdin) == -1)
	{
		perror("Error: getLine");
	}
    return line;
}

/* creates process for command */
int cmdLaunch(char *cmd, char **args)
{
    pid_t pid, wpid;
    int stats;
    
    pid = fork();       // child made
    /* error checking */
    if (pid == 0) {
        if (execvp(cmd, args) == -1)
        {
             perror("Error: fork");
        }
        return 1;
    }
    else if (pid < 0) {
        perror("lsh");
        return 2;
    }
    else {

    /* parent waits till child is done*/
    do {
      wpid = waitpid(pid, &status, WUNTRACED);
    } while (!WIFEXITED(status) && !WIFSIGNALED(status));
  }

  return 0;
}

/* determines command and executes it */
int cmdExecute(char **input)
{
    int i;
    
    if(leadCmd == NULL)
	{
		return 1;
	}
	else if( strcmp(input[0], "groups") == 0)
	{
        cmdLaunch("./groups", input);
    }
    else if(strcmp(input[0], "ls") == 0) 
    {
        cmdLaunch("./ls", input);
    }
    else if(strcmp(input[0], "cp") == 0)
    {
        cmdLaunch("./cp", input);
    }
    else if(input[0] == "cd") 
    {
        cmdLaunch("./cd", input);
    }
    else if(strcmp(input[0], "exit") == 0)
    {
        return;
    }
    else {
        system(line);
    }
    return 0;
}
