///////////////////////////////////////////


// includes
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


///////////////////////////////////////////


// prototypes
char **parse_line(char *);


///////////////////////////////////////////


// convert line into array of args
#define TOKEN_BUFFER_SIZE 16
#define TOKEN_DELIMS " \n\t"
char **parse_line(char *line)
{
	// init variables
	size_t buffer_size = TOKEN_BUFFER_SIZE;
	int pos = 0;
	char **tokens = (char **)malloc(buffer_size * sizeof(char *));
	char *token;

	// tokenize line
	token = strtok(line, TOKEN_DELIMS);
	while (token != NULL) {
		tokens[pos] = token;
		pos++;

		// if buffer fills, increase its size
		if (pos >= buffer_size) {
			buffer_size += TOKEN_BUFFER_SIZE;
			tokens = (char **)realloc(tokens, buffer_size * sizeof(char *));
		}

		// continue to tokenize
		token = strtok(NULL, TOKEN_DELIMS);
	}
	// place NULL at the end of the array and return
	// for ease in looping later, also execvp expects this
	tokens[pos] = NULL;
	return tokens;
}
// strtok tutorial: https://www.tutorialspoint.com/c_standard_library/c_function_strtok.htm

/*
STATEMENT OF NON-PLAGIARISM
		I hereby declare that all information in this assignment has been obtained and presented in
		accordance with academic rules and ethical conduct and the work I am submitting in this
		document, except where I have indicated, is my own work.
			Student Number: 19425804
			Student Name: Conor Joyce
			Date: 25/03/2021
*/
