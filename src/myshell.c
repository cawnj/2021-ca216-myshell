///////////////////////////////////////////
//
//       myshell
//                ~joycec27
//
//   ca216 university assignment
//
///////////////////////////////////////////
//
//  All references are underneath the 
///   function in which they were used.
//
///////////////////////////////////////////


// includes
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "shell-input.h"
#include "shell-exec.h"
#include "filerw.h"


///////////////////////////////////////////


// prototypes
void loop(void);
void batch_mode(char const *arg);
void set_shell_env(void);


///////////////////////////////////////////


// perform some jobs and start input loop
int main(int argc, char const *argv[])
{
	set_shell_env();

	// if arg given, batch mode
	if (argc > 1) {
		batch_mode(argv[1]);
		exit(EXIT_SUCCESS);
	}

	// init variables and enable tab autocomplete
	char *line, prompt[100];
	char **args;
	int status = 1;
	rl_bind_key('\t', rl_complete);
	
	// shell loop
	do {
		// prompt
		snprintf(prompt, sizeof(prompt), "%s%s%s$ ", "\e[1;34m", getcwd(NULL, 1024), "\e[0m");

		// read line and parse into array of args
		line = readline(prompt);
		args = parse_line(line);

		// args to exec handler and return status 1/0
		status = exec_handler(args);

		// free memory
		free(line);
		free(args);

	} while(status); // while status is 1
}
// tab auto-completion: https://stackoverflow.com/a/31166621
// loop process: https://brennan.io/2015/01/16/write-a-shell-in-c/#basic-loop-of-a-shell


// run commands from a file
void batch_mode(char const *filename)
{
	// init variables
	char **lines;
	char **args;
	
	// read lines from file into array
	lines = read_from_file(filename);

	for (int i = 0; lines[i] != NULL; i++) {
		// parse each line into args and exec
		args = parse_line(lines[i]);
		exec_handler(args);
	}
	
	// free memory
	free(lines);
	free(args);
}


// set SHELL environment variable
void set_shell_env(void)
{
	// previously was readlink("/proc/self/exe"...) but this does not work without root
	// so instead strcat current working directory and /myshell
	// set concatenated string as SHELL environment variable
	char cwd[PATH_MAX];
	getcwd(cwd, sizeof(cwd));
	setenv("STARTUP_DIR", cwd, 1);
	setenv("SHELL", strcat(cwd, "/myshell"), 1);
}
// finding process full path: https://stackoverflow.com/questions/5525668/how-to-implement-readlink-to-find-the-path

// the end :)

/*
STATEMENT OF NON-PLAGIARISM
		I hereby declare that all information in this assignment has been obtained and presented in
		accordance with academic rules and ethical conduct and the work I am submitting in this
		document, except where I have indicated, is my own work.
			Student Number: 19425804
			Student Name: Conor Joyce
			Date: 25/03/2021
*/
