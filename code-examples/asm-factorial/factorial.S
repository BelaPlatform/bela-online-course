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
	.align 2							@ Align the function code to a 4-byte (2^2) word boundary.
	.arm								@ Use ARM instructions instead of Thumb.
	.type factorialInAsm, %function		@ Declare that this is a function
	.global factorialInAsm 				@ Set this function to be global (accessible from outside)
factorialInAsm:							@ Declare the function (arguments in r0-r3)
	@ TODO: input argument is in r0;
	@       move it to r1 so we can use r0 for the return value
	@ TODO: then begin by setting r0 = 1
	@       check if r1 <= 0
	@       if yes, branch to the end (nothing to do)
factorialLoop:
	@ TODO: in here, multiply r0 by the latest r1
	@       then decrement r1 (i.e. r1 = r1 - 1)
	@       check if r1 is equal to 0, otherwise loop
factorialDone:
	bx lr					@ Return (return value is in r0)
