@  ____  _____ _        _    
@ | __ )| ____| |      / \   
@ |  _ \|  _| | |     / _ \  
@ | |_) | |___| |___ / ___ \ 
@ |____/|_____|_____/_/   \_\
@
@ http://bela.io
@
@ C++ Real-Time Audio Programming with Bela - Lecture 21: ARM assembly language

@ Simple assembly functions for ARM
@ Partially derived from these sources:
@  http://shervinemami.info/armAssembly.html
@  http://stackoverflow.com/questions/18841693/c-code-calling-an-assembly-routine-arm

@ Declare unified (ARM and Thumb) syntax
 	.syntax unified
 	.section .text

@ Functions pass the first four arguments on r0, r1, r2 and r3
@ Return values come back on r0.
@ r12 can be modified without restoring at the end
@ Don't touch r13-r15.
@ Other registers can be modified if restored at the end

@ Use the following lines before ANY function:

	.align 2						@ Align the function code to a 4-byte (2^2) word boundary.
	.arm							@ Use ARM instructions instead of Thumb.
	
@ Declaration of functions:	
	
	.global addNumbers 				@ Set this function to be global (accessible from outside)
	.type addNumbers, %function		@ Declare that this is a function
addNumbers:							@ Declare the function (arguments in r0-r3)
	add r0, r0, r1					@ r0 = r0 + r1
	bx lr							@ Return (return value is in r0)
	