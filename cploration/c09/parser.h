/****************************************
 * C-ploration 6 for CS 271
 * 
 * [NAME] $Austen_Turbyne$
 * [TERM] FALL $2023$
 * 
 ****************************************/

#ifndef __PARSER_H__
#define __PARSER_H__
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdint.h>
#include "hack.h"

#define MAX_LINE_LENGTH  200
#define MAX_LABEL_LENGTH (MAX_LINE_LENGTH - 2)


#define MAX_HACK_ADDRESS INT16_MAX
#define MAX_INSTRUCTIONS MAX_HACK_ADDRESS

/** function prototypes **/
char *strip(char *s);
void parse(FILE * fin);
bool is_Atype(const char *);
bool is_label(const char *);
bool is_Ctype(const char *);

typedef int16_t hack_addr;
typedef int16_t opcode;

char *extract_label(const char *line, char *label);

typedef enum instr_type {
	Invalid = -1,
	A_type,
	C_type
} instr_type; 

typedef struct c_instruction{
	opcode a:1;
	opcode comp:7;
	opcode dest:3;
	opcode jump:3;
}c_instruction;

typedef union {
    hack_addr address;
    char *label;
} address_or_label;

typedef struct a_instruction{
	address_or_label data;
	bool is_address;
}a_instruction;

typedef union A_C_instruct {
	a_instruction a;
	c_instruction c;
}A_C_instruct;

typedef struct instruction {
	A_C_instruct data;
	instr_type type;
} instruction;

void add_predefined_symbols();

bool parse_A_instruction(const char *line, a_instruction *instr);

#endif