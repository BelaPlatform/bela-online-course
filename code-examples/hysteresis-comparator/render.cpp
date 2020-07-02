/*
 ____  _____ _        _    
| __ )| ____| |      / \   
|  _ \|  _| | |     / _ \  
| |_) | |___| |___ / ___ \ 
|____/|_____|_____/_/   \_\

http://bela.io

C++ Real-Time Audio Programming with Bela - Lecture 13: State Machines
hysteresis-comparator: implement a comparator with variable threshold (hysteresis)
*/

#include <Bela.h>
#include <libraries/Scope/Scope.h>

// Oscilloscope
Scope gScope;

// Pin declarations
const unsigned int kLEDPin = 0;					// Pin number of the LED
const unsigned int kInputPin = 0;				// Pin number of the analog input

// TODO: declare states and high and low thresholds here
float gThreshold = 0.5;

bool setup(BelaContext *context, void *userData)
{
	// Check that we have the expected analog and digital I/O
	if(context->digitalFrames != 2*context->analogFrames) {
		rt_fprintf(stderr, "This example expects analog inputs at half the digital sample rate.\n");
		return false;
	}	
	
	// Set LED pin to an output
	pinMode(context, 0, kLEDPin, OUTPUT);
	
	// Initialise the scope
	gScope.setup(2, context->digitalSampleRate);
	
	return true;
}

void render(BelaContext *context, void *userData)
{
   for(unsigned int n = 0; n < context->digitalFrames; n++) {
   		// Read the analog pin
   		float reading = analogRead(context, n/2, kInputPin);
   		int output = 0;
   	
		// TODO: replace this with a hysteresis comparator: different threshold in each state
   		if(reading > gThreshold) {
   			output = 1;
   		}

   		// Write the state to the scope and LED
   		digitalWriteOnce(context, n, kLEDPin, output);
   		gScope.log(reading, (float)output);
    }
}

void cleanup(BelaContext *context, void *userData)
{

}