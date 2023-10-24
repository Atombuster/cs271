/****************************************
 * C-ploration 4 for CS 271
 * 
 * [NAME] $Austen_Turbyne$
 * [TERM] FALL $2023$
 * 
 ****************************************/
#include "parser.h"


//We start with an empty main(..) function that accepts arguments. 
int main(int argc, const char *argv[]) {		

	// Check that one argument has been passed
	if (argc != 2) {
	// if incorrect number of arguments
		printf("Usage: %s [filename]\n", argv[0]);
		exit(EXIT_FAILURE);
	}
	//Open the argument passed as a file and save it as a file pointer
	FILE *fin = fopen( argv[1], "r" );
	//Check if your file pointer is NULL
	if (fin == NULL) {
		perror("Unable to open file!");
		exit(EXIT_FAILURE);
	}
	
	parse();
	
	//Close the file pointers
		fclose(fin);
		fclose(fout);
	return 0;		
}


