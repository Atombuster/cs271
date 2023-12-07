/****************************************
 * C-ploration 6 for CS 271
 * 
 * [NAME] $Austen_Turbyne$
 * [TERM] FALL $2023$
 * 
 ****************************************/
#include "parser.h"
#include "symtable.h"
#include "error.h"
#define MAX_INSTRUCTION_COUNT 30000

//We start with an empty main(..) function that accepts arguments. 
int main(int argc, const char *argv[]) {		
	
	// Check that one argument has been passed
	if (argc != 2) {
	// if incorrect number of arguments
		exit_program(EXIT_INCORRECT_ARGUMENTS, argv[0]);  
	}
	//Open the argument passed as a file and save it as a file pointer
	FILE *fin = fopen( argv[1], "r" );
	//Check if your file point1er is NULL
	if (fin == NULL) {
		exit_program(EXIT_CANNOT_OPEN_FILE, argv[1]);
	}
	
	instruction *instructions = malloc(MAX_INSTRUCTION_COUNT * sizeof(instruction));

	int num_instructions = parse(fin, instructions);
	//symtable_print_labels();
	
	//Close the file pointers
	fclose(fin);
	free(instructions);
	return 0;		
}


