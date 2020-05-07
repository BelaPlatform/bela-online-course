/*
 ____  _____ _        _    
| __ )| ____| |      / \   
|  _ \|  _| | |     / _ \  
| |_) | |___| |___ / ___ \ 
|____/|_____|_____/_/   \_\

http://bela.io

C++ Real-Time Audio Programming with Bela - Lecture 3: Wavetables
wavetable: a partially complete example implementing a wavetable
           oscillator.
*/

#include <Bela.h>
#include <libraries/Scope/Scope.h>
#include <cmath>

const int gWavetableLength = 512;		// The length of the buffer in frames
float gWavetable[gWavetableLength];		// Buffer that holds the wavetable
int gReadPointer = 0;					// Position of the last frame we played 

float gAmplitude = 0.2;					// Amplitude of the playback
float gFrequency = 220.0;				// Frequency (TODO: not implemented yet)

Scope gScope;

bool setup(BelaContext *context, void *userData)
{
	// Generate a triangle waveform (ramp from -1 to 1, then 1 to -1)
	// and store it in the buffer. Notice: generating the wavetable does 
	// not depend on the audio sample rate (why not?)
	for(unsigned int n = 0; n < gWavetableLength/2; n++) {
		gWavetable[n] = -1.0 + 4.0 * (float)n / (float)gWavetableLength;
	}
	for(unsigned int n = gWavetableLength/2; n < gWavetableLength; n++) {
		gWavetable[n] = 1.0 - 4.0 * (float)(n - gWavetableLength/2) / (float)gWavetableLength;
	}

	// Initialise the Bela oscilloscope
	gScope.setup(1, context->audioSampleRate);

	return true;
}

void render(BelaContext *context, void *userData)
{
    for(unsigned int n = 0; n < context->audioFrames; n++) {
    	// Load a sample from the buffer
        float out = gAmplitude * gWavetable[gReadPointer];

        // Increment read pointer and reset to 0 when end of table is reached
        // TODO: update this code to handle different frequencies!
        gReadPointer++;
        if(gReadPointer >= gWavetableLength)
            gReadPointer = 0;
            
    	for(unsigned int channel = 0; channel < context->audioOutChannels; channel++) {
			// Write the sample to every audio output channel
    		audioWrite(context, n, channel, out);
    	}
    	
    	// Write the sample to the oscilloscope
    	gScope.log(out);
    }
}

void cleanup(BelaContext *context, void *userData)
{

}
