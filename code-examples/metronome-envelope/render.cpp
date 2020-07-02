/*
 ____  _____ _        _    
| __ )| ____| |      / \   
|  _ \|  _| | |     / _ \  
| |_) | |___| |___ / ___ \ 
|____/|_____|_____/_/   \_\

http://bela.io

C++ Real-Time Audio Programming with Bela - Lecture 13: State Machines
metronome-envelope: metronome code using an exponential envelope rather than a sample
*/

#include <Bela.h>
#include <math.h>

// Oscillator variables
float gPhase = 0;			// Current phase
float gFrequency = 1000;	// Frequency in Hz

// Envelope variables
float gAmplitude = 1.0;   
float gEnvelopeScaler = 0.997;

// Metronome state machine variables
// TODO: declare variables for which beat (state) we're on
int gMetronomeCounter = 0;
int gMetronomeInterval = 0;

// setup() only runs one time
bool setup(BelaContext *context, void *userData)
{
	// Calculate the metronome interval based on 120 bpm
	float bpm = 120.0;
	gMetronomeInterval = 60.0 * context->audioSampleRate / bpm;
	
    return true;
}

// render() is called every time there is a new block to calculate
void render(BelaContext *context, void *userData)
{
   	// This for() loop goes through all the samples in the block
	for (unsigned int n = 0; n < context->audioFrames; n++) {
		
		// Increment counter and check if it has reached the interval
		if(++gMetronomeCounter >= gMetronomeInterval) {
			// Metronome tick elapsed; reset counter and envelope
			gMetronomeCounter = 0;
			gAmplitude = 1.0;
		}
		
		gAmplitude *= gEnvelopeScaler;
		
	    // Calculate a sample of the sine wave, and scale by the envelope
		gPhase += 2.0 * M_PI * gFrequency / context->audioSampleRate;
		if(gPhase >= 2.0 * M_PI)
			gPhase -= 2.0 * M_PI;
		float out = gAmplitude * sin(gPhase);

		// Write the sample to the audio output buffer
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
