// This file is part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.
// File name: projects/04/Fill.asm

// Runs an infinite loop that listens to the keyboard input.
// When a key is pressed (any key), the program blackens the screen,
// i.e. writes "black" in every pixel;
// the screen should remain fully black as long as the key is pressed. 
// When no key is pressed, the program clears the screen, i.e. writes
// "white" in every pixel;
// the screen should remain fully clear as long as no key is pressed.

// Put your code here.


(Start) //set ram1 to 0
@R1
M=0

@8191
D=A
@R2 // now is 8191
M=D

@SCREEN
D=A
@R3 // now 1 before screen
M=D

@KBD
D=A
@R0 // now at key part
M=D


(keychecker) // a loop that goes threw all keys seeing if pressed (pressed putting a 1 in ram1)

@R0
A=M //load starting key address
D=M //get key value
@R1
M=D
@IS_pressed
D;JGT

@R0
D=M
M=D
@screenreact
0;JMP

(IS_pressed)
@R0
D=M
M=D


@R1
M=-1


(screenreact) // a recusive set of code that sets screen value to ram1


@R1 
D=M
@R3
A=M //load starting screen address
M=D

@R3
D=M


@R3
M=M+1
@R2
D=M

M=M-1

@keychecker
D;JNE

@Start //restart
0;JMP