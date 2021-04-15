/*
 ____  _____ _        _    
| __ )| ____| |      / \   
|  _ \|  _| | |     / _ \  
| |_) | |___| |___ / ___ \ 
|____/|_____|_____/_/   \_\

http://bela.io

C++ Real-Time Audio Programming with Bela - Lecture 21: ARM assembly language
asm-factorial: Calculate a factorial expression in assembly language
*/

#include <Bela.h>

/* Declaration of the function which is implemented in assembly
 * Need to declare a function prototype like this (either here or
 * in a header file) so the C compiler knows how the function
 * works.
 */
extern "C" {
	int factorialInAsm(int argument);
}

// Equivalent written in C, for testing
int factorialInC(int argument) {
	// Result = argument * (argument - 1) * (argument - 2) * ... * 1
	int result = 1;
	if(argument <= 0)
		return result;
	while(argument > 0) {
		result *= argument;
		argument--;
	}
	return result;
}

bool setup(BelaContext *context, void *userData)
{
	int x = 6;	// The input to our factorial
	
	// C version
	int xfactorial = factorialInC(x);
	rt_printf("%d! = %d (C version)\n", x, xfactorial);

	// Assembly version, implemented in factorial.S
	xfactorial = factorialInAsm(x);
	rt_printf("%d! = %d (ASM version)\n", x, xfactorial);
	
    return true;
}

void render(BelaContext *context, void *userData)
{
	gShouldStop = true;		// Stop the audio rendering
}

void cleanup(BelaContext *context, void *userData)
{

}