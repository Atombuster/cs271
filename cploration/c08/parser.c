/****************************************
 * C-ploration 6 for CS 271
 * 
 * [NAME] $Austen_Turbyne$
 * [TERM] FALL $2023$
 * 
 ****************************************/

#include "symtable.h"
#include "parser.h"
#include "error.h"

/* Function: strip
 * -------------
 * remove whitespace and comments from a line
 *
 * s: the char* string to strip
 *
 * returns: the stripped char* string
 */
char *strip(char *s){	

	char s_new[strlen(s)+1];
	int i=0;
	for (char *s2 = s; *s2; s2++) { 
		if ((*s2 == '/') && (*(s2+1) == '/')) {
			break;
		}
   
		else if (!isspace(*s2)) {
			s_new[i++] = *s2;
		}
	}
	s_new[i] = '\0';
	strcpy(s, s_new);
    return s;	
}

/* Function: parse
 * -------------
 * iterate each line in the file and strip whitespace and comments. 
 *
 * file: pointer to FILE to parse
 *
 * returns: nothing
 */
void parse(FILE * fin){
	
	char line[MAX_LINE_LENGTH] = {0};
	unsigned int line_num = 0;
	unsigned int instr_num = 0;
	
	
    
	
	while (fgets(line, sizeof(line), fin)) {
		
		line_num++;
		strip(line);

		if (!(*line)){
			continue;		
		}
		char inst_type = 'C';
		inst_type=(is_Atype(line))? 'A':inst_type;

		char label[MAX_LABEL_LENGTH] = {0};
		if (is_label(line)) {
			inst_type = 'L';
			extract_label(line, label);
			if (!(isalpha(label[0]))){
				exit_program(EXIT_INVALID_LABEL, line_num, label);
			}
			if ((symtable_find(label) != NULL)){
				exit_program(EXIT_SYMBOL_ALREADY_EXISTS, line_num, label);
			}
			symtable_insert(label, instr_num);
			continue;	
				
		}
		
		if (instr_num > MAX_INSTRUCTIONS){
			exit_program(EXIT_TOO_MANY_INSTRUCTIONS, MAX_INSTRUCTIONS + 1);
		}
		
		printf("%u: %c  %s\n", instr_num, inst_type, line);
		instr_num++;

	}
	
	
}
 //determine if our input string is an A-type instruction
bool is_Atype(const char *line){
	if (*line == '@'){
		return true;
	}else {
		return false;
	}
}
// check if label
bool is_label(const char *line){
	if (*line == '(' && line[strlen(line)-1] == ')'){
			return true;
	}
	
	return false;	
	
}
// check if C-type instruction
bool is_Ctype(const char *line){
	if (!is_Atype(line) && !is_label(line)){
		return true;
	}
	return false;
}

char *extract_label(const char *line, char *label){
	
	int i=0;
	for (const char *line2 = line; *line2; line2++) { 
		if ((*line2 == '(') || (*line2 == ')')) {
		continue;
		}
	
		else if (!isspace(*line2)) {
			label[i++] = *line2;
		}
	}
	label[i] = '\0';
	
    return label;
	
}

