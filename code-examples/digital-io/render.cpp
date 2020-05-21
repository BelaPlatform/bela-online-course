/*
 ____  _____ _        _    
| __ )| ____| |      / \   
|  _ \|  _| | |     / _ \  
| |_) | |___| |___ / ___ \ 
|____/|_____|_____/_/   \_\

http://bela.io

C++ Real-Time Audio Programming with Bela - Lecture 7: Digital I/O
digital-io: a test project using a button and LED to control a noise source
*/

#include <Bela.h>
#include <libraries/Scope/Scope.h>

// Pin definitions: see the pin diagram in the IDE for the wiring
const int kButtonPin = 1;
const int kLedPin = 0;

// Bela oscilloscope
Scope gScope;

bool setup(BelaContext *context, void *userData)
{
	// Check that audio and digital have the same number of frames
	// per block, an assumption made in render()
	if(context->audioFrames != context->digitalFrames) {
		rt_fprintf(stderr, "This example needs audio and digital running at the same rate.\n");
		return false;
	}
	
	// Set the mode of digital pins
	pinMode(context, 0, kButtonPin, INPUT); 
	pinMode(context, 0, kLedPin, OUTPUT);
	
	// Initialise the Bela oscilloscope with 2 channels
	gScope.setup(2, context->audioSampleRate);
	
	return true;
}


void render(BelaContext *context, void *userData)
{
	for(unsigned int n = 0; n < context->audioFrames; n++) {
		float out = 0;
		
		// Read the digital input
		int status = digitalRead(context, n, kButtonPin);
		
		if(status == LOW) {
			// Reading LOW (0) means button was pressed
			
			// Generate white noise: random values between -1 and 1
			float noise = 2.0 * (float)rand() / (float)RAND_MAX - 1.0;
			out = noise * 0.1;
			
			// Turn on LED
			digitalWriteOnce(context, n, kLedPin, HIGH);
		}
		else {
			// Turn off LED
			digitalWriteOnce(context, n, kLedPin, LOW);
		}
		
    	for(unsigned int channel = 0; channel < context->audioOutChannels; channel++) {
			// Write the sample to every audio output channel
    		audioWrite(context, n, channel, out);
    	}
    	
    	// Log the digital input and the audio output to the scope
    	gScope.log(status, out);
	}
}


void cleanup(BelaContext *context, void *userData)
{
	// Nothing to do here
}
