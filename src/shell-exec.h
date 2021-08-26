///////////////////////////////////////////


// includes
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include "builtin.h"


///////////////////////////////////////////


// prototypes
int exec_handler(char**);
int exec_external(char**);


///////////////////////////////////////////


// function decides on how to execute
int exec_handler(char **args)
{
	// if no args, exit
	if (args[0] == NULL) {
		return 1;
	}

	// loop and compare to each builtin function
	for (int i = 0; i < num_builtins(); i++)
	{
		if (!strcmp(args[0], builtin_str[i])) {
			// on a match, run corresponding builtin function
			return (*builtin_func[i])(args);
		}
	}
	
	// no match found above
	// run external program instead
	return exec_external(args);
}
// builtin handling: https://brennan.io/2015/01/16/write-a-shell-in-c/#putting-together-builtins-and-processes


// execute external programs
int exec_external(char **args)
{
	// init variables
	pid_t pid;
	int status;

	// fork
	pid = fork();

	// child enters this if statement
	if (pid == 0) {
		// replace child with another process
		// error handling if execvp returns less than 0
		if (execvp(args[0], args) < 0)
			printf("command not found: %s\n", args[0]);

		// if the child even gets this far without being replaced,
		// something went horribly wrong
		exit(EXIT_FAILURE);
	}
	// parent enters this else statement
	else {
		// parent ignores interrupts
		// so it doesn't close on a ctrl-c meant for the child only
		signal(SIGINT, SIG_IGN);

		// wait until child is finished
		waitpid(pid, &status, WUNTRACED);

		// parent listens to interrupts again
		signal(SIGINT, SIG_DFL);
	}

	// return
	return 1;
}
// forking and execvp: http://www.csl.mtu.edu/cs4411.ck/www/NOTES/process/fork/exec.html

/*
STATEMENT OF NON-PLAGIARISM
		I hereby declare that all information in this assignment has been obtained and presented in
		accordance with academic rules and ethical conduct and the work I am submitting in this
		document, except where I have indicated, is my own work.
			Student Number: 19425804
			Student Name: Conor Joyce
			Date: 25/03/2021
*/
