/*
 ____  _____ _        _    
| __ )| ____| |      / \   
|  _ \|  _| | |     / _ \  
| |_) | |___| |___ / ___ \ 
|____/|_____|_____/_/   \_\

http://bela.io

C++ Real-Time Audio Programming with Bela - Lecture 13: State Machines
scope-button: show the digital input on the oscilloscope
*/

#include <Bela.h>
#include <libraries/Scope/Scope.h>

// Oscilloscope
Scope gScope;

// Pin declarations
const unsigned int kLEDPin = 0;					// Pin number of the LED
const unsigned int kButtonPin = 1;				// Pin number of the pushbutton

bool setup(BelaContext *context, void *userData)
{
	// Set LED pin to an output
	pinMode(context, 0, kLEDPin, OUTPUT);
	// Set button pin to an input
	pinMode(context, 0, kButtonPin, INPUT);
	
	// Initialise the scope
	gScope.setup(1, context->digitalSampleRate);
	
	return true;
}

void render(BelaContext *context, void *userData)
{
   for(unsigned int n = 0; n < context->digitalFrames; n++) {
   		// Read the button state
   		int value = digitalRead(context, n, kButtonPin);
   		
   		// Write the state to the scope
   		gScope.log((float)value);
   		
   		// Write the inverted output to the LED (since button is active low)
   		digitalWriteOnce(context, n, kLEDPin, !value);
    }
}

void cleanup(BelaContext *context, void *userData)
{

}