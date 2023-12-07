#ifndef __HACK_H__



#define NUM_PREDEFINED_SYMBOLS 23

typedef enum symbol_id {
		SP = 0,
		LCL = 1,
		ARG = 2,
		THIS = 3,
		THAT = 4,
		R0 = 0,
		R1 = 1,
		R2 = 2,
		R3 = 3,
		R4 = 4,
		R5 = 5,
		R6 = 6,
		R7 = 7,
		R8 = 8,
		R9 = 9,
		R10 = 10,
		R11 = 11,
		R12 = 12,
		R13 = 13,
		R14 = 14,
		R15 = 15,
		SCREEN = 16384,
		KBD = 24576
		
}symbol_id;

typedef struct predefined_symbol{
	char name[NUM_PREDEFINED_SYMBOLS];
	int16_t address;
}predefined_symbol;

static const predefined_symbol predefined_symbols[NUM_PREDEFINED_SYMBOLS] = {
    {"R0", R0}, 
    {"R1", R1}, 
	{"R2", R2},
	{"R3", R3},
	{"R4", R4},
	{"R5", R5},
	{"R6", R6},
	{"R7", R7},
	{"R8", R8},
	{"R9", R9},
	{"R10", R10},
	{"R11", R11},
	{"R12", R12},
	{"R13", R13},
	{"R14", R14},
	{"R15", R15},
	{"SP", SP},
	{"LCL", LCL},
	{"ARG", ARG},
	{"THIS", THIS},
	{"THAT", THAT},
	{"SCREEN", SCREEN},
	{"KBD", KBD}
};

typedef enum comp_id {
	//A=0
	COMP_INVALID = -1,
	COMP_0 = 42,
	COMP_1 = 63,
	COMP_NEG1 = 58,
	COMP_D = 12,
	COMP_A = 48,
	COMP_NOTD = 13,
	COMP_NOTA = 49,
	COMP_NEGD = 15,
	COMP_NEGA = 51,
	COMP_DPLUS1 = 31,
	COMP_APLUS1 = 55,
	COMP_DMINUS1 = 14,
	COMP_AMINUS1 = 50,
	COMP_DPLUSA = 2,
	COMP_DMINUSA = 19,
	COMP_AMINUSD = 7,
	COMP_DANDA = 0,
	COMP_DORA = 21,
	//A=1
	COMP_M = 48,
	COMP_NOTM = 49,
	COMP_NEGM = 51,
	COMP_MPLUS1 = 55,
	COMP_MMINUS1 = 50,
	COMP_DPLUSM = 2,
	COMP_DMINUSM = 19,
	COMP_MMINUSD = 7,
	COMP_DANDM = 0,
	COMP_DORM = 21,

}comp_id;

typedef enum dest_id {
	DEST_INVALID = -1,
	DEST_NULL,//0
	DEST_M,//1
	DEST_D,//2
	DEST_MD,//3
	DEST_A,//4
	DEST_AM,//5
	DEST_AD,//6
	DEST_AMD//7
}dest_id;

typedef enum jump_id {
	JMP_INVALID = -1,
	JMP_NULL = 0, // var in emum always increase by 1 per line
	JMP_JGT = 1, //this is for ez reading
	JMP_JEQ = 2,
	JMP_JGE = 3,
	JMP_JLT = 4,
	JMP_JNE = 5,
	JMP_JLE = 6,
	JMP_JMP = 7
}jump_id;



static inline jump_id str_to_jumpid(const char *s) {
    jump_id id = JMP_INVALID;

    if (s == NULL) {
        id = JMP_NULL;
    } else if (strcmp(s, "JGT") == 0) {
        id = JMP_JGT;
    } else if (strcmp(s, "JEQ") == 0) {
        id = JMP_JEQ;
    } else if (strcmp(s, "JGE") == 0) {
        id = JMP_JGE;
    } else if (strcmp(s, "JLT") == 0) {
        id = JMP_JLT;
    } else if (strcmp(s, "JNE") == 0) {
        id = JMP_JNE;
    } else if (strcmp(s, "JLE") == 0) {
        id = JMP_JLE;
    } else if (strcmp(s, "JMP") == 0) {
        id = JMP_JMP;		
	}
	
    return id;
}

static inline dest_id str_to_destid(const char *s) {
    dest_id id = DEST_INVALID; 
    if (s == NULL) { 
        id = DEST_NULL;
    } else if (strcmp(s, "M") == 0) { 
        id = DEST_M;
    } else if (strcmp(s, "D") == 0) {
        id = DEST_D;
    } else if (strcmp(s, "MD") == 0) {
        id = DEST_MD;
    } else if (strcmp(s, "A") == 0) {
        id = DEST_A;
    } else if (strcmp(s, "AM") == 0) {
        id = DEST_AM;
    } else if (strcmp(s, "AD") == 0) {
        id = DEST_AD;
    } else if (strcmp(s, "AMD") == 0) {
        id = DEST_AMD;
    }
    return id; 
}


static inline comp_id str_to_compid(const char *s, int *a) {
    comp_id id = COMP_INVALID; 
    if (s == NULL) { 
        return id;
    }
 
    if (strcmp(s, "0") == 0) {
        id = COMP_0;
        *a = 0;
    } else if (strcmp(s, "1") == 0) {
        id = COMP_1;
        *a = 0;
    } else if (strcmp(s, "-1") == 0) {
        id = COMP_NEG1;
        *a = 0;
    } else if (strcmp(s, "D") == 0) {
        id = COMP_D;
        *a = 0;
    } else if (strcmp(s, "A") == 0) {
        id = COMP_A;
        *a = 0;
    } else if (strcmp(s, "!D") == 0) {
        id = COMP_NOTD;
        *a = 0;
    } else if (strcmp(s, "!A") == 0) {
        id = COMP_NOTA;
        *a = 0;
    } else if (strcmp(s, "-D") == 0) {
        id = COMP_NEGD;
        *a = 0;
    } else if (strcmp(s, "-A") == 0) {
        id = COMP_NEGA;
        *a = 0;
    } else if (strcmp(s, "D+1") == 0) {
        id = COMP_DPLUS1;
        *a = 0;
    } else if (strcmp(s, "A+1") == 0) {
        id = COMP_APLUS1;
        *a = 0;
    } else if (strcmp(s, "D-1") == 0) {
        id = COMP_DMINUS1;
        *a = 0;
    } else if (strcmp(s, "A-1") == 0) {
        id = COMP_AMINUS1;
        *a = 0;
    } else if (strcmp(s, "D+A") == 0) {
        id = COMP_DPLUSA;
        *a = 0;
    } else if (strcmp(s, "D-A") == 0) {
        id = COMP_DMINUSA;
        *a = 0;
    } else if (strcmp(s, "A-D") == 0) {
        id = COMP_AMINUSD;
        *a = 0;
    } else if (strcmp(s, "D&A") == 0) {
        id = COMP_DANDA;
        *a = 0;
    } else if (strcmp(s, "D|A") == 0) {
        id = COMP_DORA;
        *a = 0;
    } else if (strcmp(s, "M") == 0) {
        id = COMP_M;
        *a = 1;
    } else if (strcmp(s, "!M") == 0) {
        id = COMP_NOTM;
        *a = 1;
    } else if (strcmp(s, "-M") == 0) {
        id = COMP_NEGM;
        *a = 1;
    } else if (strcmp(s, "M+1") == 0) {
        id = COMP_MPLUS1;
        *a = 1;
    } else if (strcmp(s, "M-1") == 0) {
        id = COMP_MMINUS1;
        *a = 1;
    } else if (strcmp(s, "D+M") == 0) {
        id = COMP_DPLUSM;
        *a = 1;
    } else if (strcmp(s, "D-M") == 0) {
        id = COMP_DMINUSM;
        *a = 1;
    } else if (strcmp(s, "M-D") == 0) {
        id = COMP_MMINUSD;
        *a = 1;
    } else if (strcmp(s, "D&M") == 0) {
        id = COMP_DANDM;
        *a = 1;
    } else if (strcmp(s, "D|M") == 0) {
        id = COMP_DORM;
        *a = 1;
    }
    return id;
}



#endif