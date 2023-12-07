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
int parse(FILE * fin, instruction *instructions){
	instruction instr;
	char line[MAX_LINE_LENGTH] = {0};
	unsigned int line_num = 0;
	unsigned int instr_num = 0;
	add_predefined_symbols();
	
    
	
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
				
		} else if (inst_type == 'A'){
			if (!parse_A_instruction(line, &instr.data.a)){
				exit_program(EXIT_INVALID_A_INSTR, line_num, line);
			}
			instr.type = A_type;
			if (!instr.data.a.is_address){
				printf("A: %s\n", instr.data.a.data.label);
			}
			if (instr.data.a.is_address){
				printf("A: %d\n", instr.data.a.data.address);
			}
		} else if (inst_type == 'C'){
			char tmp_line[MAX_LINE_LENGTH + 1];
			strcpy(tmp_line, line);
			parse_C_instruction(tmp_line, &instr.data.c);
			if (instr.data.c.dest == DEST_INVALID) {
				exit_program(EXIT_INVALID_C_DEST, line_num, line);
			}
			if (instr.data.c.comp == COMP_INVALID) {
				exit_program(EXIT_INVALID_C_COMP, line_num, line);
			}
			if (instr.data.c.jump == JMP_INVALID) {
				exit_program(EXIT_INVALID_C_JUMP, line_num, line);
			}
			instr.type = C_type;
			printf("C: d=%d, c=%d, j=%d\n", instr.data.c.dest, instr.data.c.comp, instr.data.c.jump);
		}
		
		
		if (instr_num > MAX_INSTRUCTIONS){
			exit_program(EXIT_TOO_MANY_INSTRUCTIONS, MAX_INSTRUCTIONS + 1);
		}
		
		//printf("%u: %c  %s\n", instr_num, inst_type, line);
		instructions[instr_num++] = instr;

	}
	
	return instr_num;
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

void add_predefined_symbols(){
	for(int i = 0; i < NUM_PREDEFINED_SYMBOLS; i++){
		predefined_symbol tuple = predefined_symbols[i];
		symtable_insert(tuple.name, tuple.address);
		
	}
}


bool parse_A_instruction(const char *line, a_instruction *instr){
	char *s = (char*)malloc(strlen(line));
    strcpy(s, line + 1);
    char *s_end = NULL;
    long result = strtol(s, &s_end, 10);

    if (s == s_end) {
        instr->data.label = (char*)malloc(strlen(line));
        strcpy(instr->data.label, s);
        instr->is_address = false;
    } else if (*s_end != 0) {
        return false;
    } else {
        instr->data.address = result;
        instr->is_address = true;
    }

    return true;
}


void parse_C_instruction(char *line, c_instruction *instr) {
    char *temp, *jump, *dest, *comp;
	

    temp = strtok(line, ";");
    jump = strtok(NULL, ";");


    dest = strtok(temp, "=");
    comp = strtok(NULL, "=");

    if (comp == NULL) {
        comp = dest;
        dest = NULL;
    }
	
	int a = -1;
    instr->jump = str_to_jumpid(jump);
    instr->comp = str_to_compid(comp, &a); 
    instr->dest = str_to_destid(dest);
	instr->a = a;
}



