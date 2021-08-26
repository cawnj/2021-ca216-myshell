///////////////////////////////////////////


// includes
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include <dirent.h> 
#include <string.h>
#include <libgen.h>


///////////////////////////////////////////


// prototypes
int builtin_quit(char **args);
int builtin_cd(char ** args);
int builtin_clr(char **args);
int builtin_dir(char **args);
int builtin_environ(char **args);
int builtin_echo(char **args);
int builtin_help(char **args);
int builtin_pause(char **args);


///////////////////////////////////////////


// string array of all builtins
char *builtin_str[] = {
	"cd",
	"clr",
	"dir",
	"environ",
	"echo",
	"help",
	"pause",
	"quit",
};


// pointer array to all functions
// index of each function refers to its string counterpart above
int (*builtin_func[])(char **args) = {
	&builtin_cd,
	&builtin_clr,
	&builtin_dir,
	&builtin_environ,
	&builtin_echo,
	&builtin_help,
	&builtin_pause,
	&builtin_quit,
};
// function pointer arrays explained: https://stackoverflow.com/a/252752
// inspiration from: https://brennan.io/2015/01/16/write-a-shell-in-c/#shell-builtins


// simple function to calculate how many builtins we have
int num_builtins() {
  return sizeof(builtin_str) / sizeof(char *);
}


///////////////////////////////////////////


// quit - returns 0, breaking input loop
int builtin_quit(char **args)
{
	printf("Goodbye!\n");
	return 0;
}


// cd
int builtin_cd(char ** args)
{
	// if no arguments, print current dir
	if (args[1] == NULL) {
		printf("%s\n", getenv("PWD"));
	}
	// change dir, error if chdir does not return 0
	else if (chdir(args[1]) != 0) {
		perror("cd");
	}
	// set PWD environment variable on success
	else {
		char cwd[PATH_MAX];
		getcwd(cwd, sizeof(cwd));
		setenv("PWD", cwd, 1);
	}
	
	return 1;
}
// chdir: https://stackoverflow.com/questions/56031104/the-cd-command-in-c-and-use-of-chdir


// clr - runs system command clear
int builtin_clr(char **args)
{
	system("clear");
	return 1;
}


// dir
int builtin_dir(char **args)
{
	// create dir pointer
	DIR *d;
	struct dirent *dir;
	
	// if no args, open current directory
	if (args[1] == NULL) {
		d = opendir(".");
	}
	// if args, open given directory instead
	else {
		d = opendir(args[1]);\
	}
	
	// if directory exists
	if (d) {
		// loop reading directory, and print filenames
		while ((dir = readdir(d)) != NULL)
			printf("%s\n", dir->d_name);
		// close dir
		closedir(d);
	} else perror("dir"); // if directory does not exist, error

	return 1;
}
// listing all files in a directory: https://www.tutorialspoint.com/c-program-to-list-all-files-and-sub-directories-in-a-directory


// environ - loop through environ array and print
int builtin_environ(char **args)
{
	extern char **environ;
	for (int i = 0; environ[i] != NULL ; i++){
		printf("%s\n", environ[i]);
	}
	return 1;
}


// echo - extended to support environment variables
int builtin_echo(char **args)
{
	// loop from 1 to skip first arg
	// which is echo
	for (int i = 1; args[i] != NULL; i++)
	{
		// store current arg in a variable for ease of use
		char *arg = args[i];

		// if first char of arg is $
		// we want to print an environment variable instead
		if (arg[0] == '$') {
			// store desired len, init str
			size_t len = strlen(arg)-1;
			char env[len];

			// copy first arg excluding first char $ into str variable
			// place null character at the end
			strncpy(env, &arg[1], len);
			env[len] = '\0';

			// print desired environment variable
			printf("%s ", getenv(env));
		}
		// standard case, not an environment variable
		else {
			printf("%s ", arg);
		}
	}

	// finish with a newline and return
	printf("\n");
	return 1;
}
// substring with strncpy: https://www.delftstack.com/howto/c/get-c-substring/#strncpy-function-to-get-a-substring-in-c


// help - run more with manual file
int builtin_help(char **args)
{
	// variable spaghetti to ensure help can be run from any directory once in the shell
	// as long as myshell isnt moved!!
	char cmd[PATH_MAX];
	char *startup_dir = getenv("STARTUP_DIR");
	snprintf(cmd, sizeof(cmd), "more %s%s", startup_dir, "/../manual/readme");
	system(cmd);
	return 1;
}


// pause
int builtin_pause(char **args)
{
	printf("Press enter to continue...\n");

	// init char
	char ch;

	// loop forever
	while(1) {
		// get char from stdin
		ch = fgetc(stdin);

		// if char is enter, exit
		if (ch == 10 || ch == EOF) {
			return 1;
		}
	}

	// how did we get here?!?
	// just in case
	return 1;
}
// enter key ascii: https://www.includehelp.com/code-snippets/how-to-identify-enter-key-is-pressed-in-c-programming-language.aspx

/*
STATEMENT OF NON-PLAGIARISM
		I hereby declare that all information in this assignment has been obtained and presented in
		accordance with academic rules and ethical conduct and the work I am submitting in this
		document, except where I have indicated, is my own work.
			Student Number: 19425804
			Student Name: Conor Joyce
			Date: 25/03/2021
*/
