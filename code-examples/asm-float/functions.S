@  ____  _____ _        _    
@ | __ )| ____| |      / \   
@ |  _ \|  _| | |     / _ \  
@ | |_) | |___| |___ / ___ \ 
@ |____/|_____|_____/_/   \_\
@
@ http://bela.io
@
@ C++ Real-Time Audio Programming with Bela - Lecture 21: ARM assembly language

@ Simple assembly example for ARM using
@ vector floating point (VFP) unit and
@ hardfp EABI

@ Declare unified (ARM and Thumb) syntax
 	.syntax unified
 	.arch armv7-a
	.fpu vfpv3-d16
 	.section .text

@ Functions pass the first four arguments on r0, r1, r2 and r3
@ Return values come back on r0.
@ r12 can be modified without restoring at the end
@ Don't touch r13-r15.
@ Other registers can be modified if restored at the end

@ Use the following lines before ANY function:

	.align 2						@ Align the function code to a 4-byte (2^2) word boundary.
	.arm							@ Use ARM instructions instead of Thumb.
	
	.type multiplyFloatsAsm, %function		@ Declare that this is a function
	.global multiplyFloatsAsm 				@ Set this function to be global (accessible from outside)
multiplyFloatsAsm:							@ Declare the function (arguments in r0-r3 or s0-s3)
    @ You would need the next two lines in softfp ABI but not in hard ABI!
	@ vmov s0, r0				@ Move ARM register r0 to VFP register s0
	@ vmov s1, r1				@ Move ARM register r1 to VFP register s1

	vmul.f32 s0, s0, s1			@ Single-precision multiply

	@ This line would only be needed in softfp ABI
	@ vmov r0, s0				@ Move result back to ARM r0
	bx lr						@ Return (return value is in r0)

	.type distance, %function	@ Declare that this is a function
	.global distance 			@ Set this function to be global (accessible from outside)
distance:						@ Declare the function (arguments in s0-s3)
	@ TODO!						@ result = sqrt((x2 - x1)^2 + (y2 - y1)^2)
	bx lr						@ Return (return value is in s0)
