#include "symtable.h"

Symbol* hashArray[SYMBOL_TABLE_SIZE]; 

int hash(char *str){
    unsigned long hash = 5381;
    int c;
	
    while ((c = *str++)) {
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
	}
    return hash % SYMBOL_TABLE_SIZE;
	
}
	
void symtable_insert(char *name, hack_addr addr){
	Symbol *item = (Symbol*) malloc(sizeof(Symbol));
	item->addr = addr;  
	item->name = name;
	//test
	printf("KEY INSERTED TO SYMTABLE: %s\n",name);
	printf("ADDR INSERTED TO SYMTABLE: %d\n",addr);
	//get the hash 
	int hashIndex = hash(name);

	//move in array until an empty or deleted cell
	while(hashArray[hashIndex] != NULL && hashArray[hashIndex]->name) {
	//go to next cell
      ++hashIndex;
		
      //wrap around the table
     hashIndex %= SYMBOL_TABLE_SIZE;
   }
	
   hashArray[hashIndex] = item;
}

Symbol *symtable_find(char *name) {
   //get the hash 
   int hashIndex = hash(name);  
	
   //move in array until an empty 
   while(hashArray[hashIndex] != NULL) {
	
      if(hashArray[hashIndex]->name == name)
         return hashArray[hashIndex]; 
			
      //go to next cell
      ++hashIndex;
		
      //wrap around the table
      hashIndex %= SYMBOL_TABLE_SIZE;
   }        
	
   return NULL;        
}

void symtable_display_table() {
   int i = 0;
	
   for(i = 0; i<SYMBOL_TABLE_SIZE; i++) {
	
      if(hashArray[i] != NULL)
         printf(" (%s,%d)",(hashArray[i]->name),hashArray[i]->addr);
      else
         printf(" ~~ ");
   }
	
   printf("\n");
}

void symtable_print_labels() {
   int i = 0;    
   for(i = 0; i<SYMBOL_TABLE_SIZE; i++) {
        if(hashArray[i] != NULL){
             printf("{%s,%d}\n",hashArray[i]->name,hashArray[i]->addr);
        }
   }
} 