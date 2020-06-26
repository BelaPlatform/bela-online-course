/*
 ____  _____ _        _    
| __ )| ____| |      / \   
|  _ \|  _| | |     / _ \  
| |_) | |___| |___ / ___ \ 
|____/|_____|_____/_/   \_\

http://bela.io

C++ Real-Time Audio Programming with Bela - Lecture 12: Envelopes
percussion: simple percussion instrument with a button and an exponential envelope
*/

#include <Bela.h>
#include <math.h>

// Digital input and analog output pin
const unsigned int kButtonPin = 0;

// Oscillator variables
float gPhase = 0;			// Current phase
float gFrequency = 1000.0;	// Frequency in Hz

// Exponential envelope variables
float gAmplitude = 1.0;     		
float gEnvelopeDecayScaler = 1.0;

// setup() only runs one time
bool setup(BelaContext *context, void *userData)
{
	// TODO: calculate the decay scaler based on the value a = 100 (see video)
    return true;
}

// render() is called every time there is a new block to calculate
void render(BelaContext *context, void *userData)
{
   	// This for() loop goes through all the samples in the block
	for (unsigned int n = 0; n < context->audioFrames; n++) {
		// TODO: check if the button is pressed; if so, reset the envelope

		// TODO: each sample, multiply the envelope by a constant to create
		// an exponential envelope
		
	    // Calculate a sample of the sine wave
		gPhase += 2.0 * M_PI * gFrequency / context->audioSampleRate;
		if(gPhase >= 2.0 * M_PI)
			gPhase -= 2.0 * M_PI;
		float out = gAmplitude * sin(gPhase);

		// This part is done for you: store the sample in the
		// audio output buffer
		for(unsigned int channel = 0; channel <context->audioOutChannels; channel++) {
		    audioWrite(context, n, channel, out);
		}
    }
}

// cleanup() runs once when the program stops
void cleanup(BelaContext *context, void *userData)
{
	// nothing to do here
}
