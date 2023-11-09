// This file is part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.
// File name: projects/04/Mult.asm

// Multiplies R0 and R1 and stores the result in R2.
// (R0, R1, R2 refer to RAM[0], RAM[1], and RAM[2], respectively.)
//
// This program only needs to handle arguments that satisfy
// R0 >= 0, R1 >= 0, and R0*R1 < 32768.

// Put your code here.


	@R2 //load r2
	M=0 //set r2 to 0
	@R1 //load r1
	D=M // D = r1
	@Invi
	D;JEQ  // in cause of a 0
	
	(Checkpoint)
	@R2 //load r2
	D=M //r2 value
	
	@R0 //Load r
	D=D+M //add
	@R2 
	M=D
	@R1
	D=M-1 // decrease R1
	M=D
	@Checkpoint
	D;JNE // to do math
	
	
	 (Invi)
	 @Invi
	 0;JMP
	 