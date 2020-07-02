/*
 ____  _____ _        _    
| __ )| ____| |      / \   
|  _ \|  _| | |     / _ \  
| |_) | |___| |___ / ___ \ 
|____/|_____|_____/_/   \_\

http://bela.io

C++ Real-Time Audio Programming with Bela - Lecture 13: State Machines
debounce: template code for debouncing a pushbutton
*/

#include <Bela.h>
#include <libraries/Scope/Scope.h>

// Oscilloscope
Scope gScope;

// Pin declarations
const unsigned int kLEDPin = 0;					// Pin number of the LED
const unsigned int kButtonPin = 1;				// Pin number of the pushbutton

// State machine states
enum {
	kStateOpen = 0,
	kStateJustClosed,
	kStateClosed,
	kStateJustOpen
};

// State machine variables
int gDebounceState = kStateOpen;
int gDebounceCounter = 0;
int gDebounceInterval = 0;

// LED on/off state
int gLEDState = 0;

bool setup(BelaContext *context, void *userData)
{
	// Set LED pin to an output
	pinMode(context, 0, kLEDPin, OUTPUT);
	// Set button pin to an input
	pinMode(context, 0, kButtonPin, INPUT);
	
	// Initialise the scope
	gScope.setup(1, context->digitalSampleRate);
	
	// TODO: calculate the debounce interval based on the sample rate for 50ms

	return true;
}

void render(BelaContext *context, void *userData)
{
   for(unsigned int n = 0; n < context->digitalFrames; n++) {
   		// Read the button state
   		int value = digitalRead(context, n, kButtonPin);
   		
   		// Write the state to the scope
   		gScope.log((float)value);
   		
   		// TODO: implement the debouncing a state machine
   		// See constants and variables at the top of the file
   		// The transition between kStateOpen and kStateJustClosed
   		// should toggle the LED.
   		
   		if(gDebounceState == kStateOpen) {
   			// Button is not pressed, could be pressed anytime
   			// Input: look for switch closure
   		}
   		else if(gDebounceState == kStateJustClosed) {
   			// Button was just pressed, wait for debounce
   			// Input: run counter, wait for timeout
   		}
   		else if(gDebounceState == kStateClosed) {
   			// Button is pressed, could be released anytime
   			// Input: look for switch opening
   		}
   		else if(gDebounceState == kStateJustOpen) {
   			// Button was just released, wait for debounce
   			// Input: run counter, wait for timeout
   		}
   		
   		// Write the LED state
   		digitalWriteOnce(context, n, kLEDPin, gLEDState);
    }
}

void cleanup(BelaContext *context, void *userData)
{

}