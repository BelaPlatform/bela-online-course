/*
 ____  _____ _        _    
| __ )| ____| |      / \   
|  _ \|  _| | |     / _ \  
| |_) | |___| |___ / ___ \ 
|____/|_____|_____/_/   \_\

http://bela.io

C++ Real-Time Audio Programming with Bela - Lecture 21: ARM assembly language
asm-test: Some simple functions implemented in ARM assembly language
*/

#include <Bela.h>

extern "C" {
	/* Declaration of the function which is implemented in assembly
	 * Need to declare a function prototype like this (either here or
	 * in a header file) so the C compiler knows how the function
	 * works. When this is used in .cpp files, it needs to be in the
	 * 'extern "C"' block.
	 */
	int addNumbers(int argumentA, int argumentB);
}

bool setup(BelaContext *context, void *userData)
{
	int x = 3;
	int y = 4;
	int z = addNumbers(x, y);	// This function is implemented in functions.S

	rt_printf("x = %d, y = %d, z = %d\n", x, y, z);
	
    return true;
}

void render(BelaContext *context, void *userData)
{
	gShouldStop = true;		// Stop the audio rendering
}

void cleanup(BelaContext *context, void *userData)
{

}