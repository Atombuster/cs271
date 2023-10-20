/****************************************
 * C-ploration 3 for CS 271
 * 
 * [NAME] $Austen_Turbyne$
 * [TERM] FALL $2023$
 * 
 ****************************************/
 #include <stdio.h>
 #include <string.h>
 #include <stdlib.h>
 #define MAX_LINE_LENGTH  200
 
	//ex1
int main(int argc, const char *argv[])
{ 
	//ex2
	if (argc != 2) {
	// if incorrect number of arguments
		printf("Usage: %s [filename]\n", argv[0]);
		exit(EXIT_FAILURE);
	}
	//ex 3
	FILE *fin = fopen( argv[1], "r" );
	if (fin == NULL) {
		perror("Unable to open file!");
		exit(EXIT_FAILURE);
	}
	
	//ex4
	char out_file[MAX_LINE_LENGTH];
	// copy argv1 to out file
	strcpy(out_file, argv[1]);
	strcat(out_file, ".echo" );
	FILE *fout = fopen(out_file, "w+" );
	//ex5 
	char line[MAX_LINE_LENGTH] = {0};
	unsigned int line_num = 0;
	while (fgets(line, sizeof(line), fin)) {
		line_num++;
		printf("[%04d] %s", line_num, line);
		fprintf(fout, "[%04d] %s", line_num, line);
	//ex6
		fclose(fin);
		fclose(fout);
	}
	
	return 1;
}