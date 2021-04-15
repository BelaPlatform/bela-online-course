/*
 ____  _____ _        _    
| __ )| ____| |      / \   
|  _ \|  _| | |     / _ \  
| |_) | |___| |___ / ___ \ 
|____/|_____|_____/_/   \_\

http://bela.io

C++ Real-Time Audio Programming with Bela - Lecture 21: ARM assembly language
asm-float: Floating point calculations in assembly language
*/

#include <Bela.h>

/* Declaration of the function which is implemented in assembly
 * Need to declare a function prototype like this (either here or
 * in a header file) so the C compiler knows how the function
 * works.
 */
extern "C" {
	/* This function implemented in functions.S */
	float multiplyFloatsAsm(float a, float b);

	/* To implement in functions.S: a function calculating the Euclidean distance between
	 * points (x1, y1) and (y1, y2).
	 */
	float distance(float x1, float y1, float x2, float y2);
}


float multiplyFloatsC(float a, float b) {
	return a * b;
}

bool setup(BelaContext *context, void *userData)
{
	// Our two input arguments
	float x = 3.01;
	float y = 2.53;

	// C version of the function
	float z = multiplyFloatsC(x, y);
	rt_printf("x = %f, y = %f, z = %f (C code)\n", x, y, z);

	// Assembly language version of the function
	z = multiplyFloatsAsm(x, y);
	rt_printf("x = %f, y = %f, z = %f (ASM code)\n", x, y, z);

	// The distance function, implemented in assembly
	float x1 = 1.0, y1 = 1.0;
	float x2 = 4.0, y2 = 5.0;
	float dist = distance(x1, y1, x2, y2);
	rt_printf("Distance from (%f, %f) to (%f, %f) = %f\n", x1, y1, x2, y2, dist);
	
    return true;
}

void render(BelaContext *context, void *userData)
{
	gShouldStop = true;		// Stop the audio rendering
}

void cleanup(BelaContext *context, void *userData)
{

}