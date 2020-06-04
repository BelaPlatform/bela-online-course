/*
 ____  _____ _        _    
| __ )| ____| |      / \   
|  _ \|  _| | |     / _ \  
| |_) | |___| |___ / ___ \ 
|____/|_____|_____/_/   \_\

http://bela.io

C++ Real-Time Audio Programming with Bela - Lecture 9: Timing
step-sequencer-metronome: cycles through a sequence of frequencies at a regular interval
*/

#include <Bela.h>
#include <libraries/Scope/Scope.h>
#include <cmath>
#include <vector>

#include "Wavetable.h"	// This is needed for the Wavetable class

// Constants that define the program behaviour
const unsigned int kWavetableSize = 512;
const float kAmplitude = 0.1;
const float kDetune = 0.005;

const unsigned int kLedPin = 0;				// Digital out for LED
const unsigned int kCVOutPin = 0;			// Analog out for CV (original Bela only)
const unsigned int kInputTempo = 0;			// Which analog input to read

// TODO: declare global variables here for counting time

// Browser-based oscilloscope
Scope gScope;

// Wavetable oscillators
Wavetable gOscillators[2];

// Step sequencer contents
std::vector<float> gSequencerBuffer = {36, 48, 39, 51, 53, 41, 55, 43};
unsigned int gSequencerLocation = 0;

bool setup(BelaContext *context, void *userData)
{
	std::vector<float> wavetable;
	
	// Check that audio and digital have the same number of frames
	// per block, an assumption made in render()
	if(context->audioFrames != context->digitalFrames) {
		rt_fprintf(stderr, "This example needs audio and digital running at the same rate.\n");
		return false;
	}
		
	// Populate a buffer with the first 32 harmonics of a sawtooth wave
	wavetable.resize(kWavetableSize);
	for(unsigned int n = 0; n < wavetable.size(); n++) {
		wavetable[n] = 0;
		for(unsigned int harmonic = 1; harmonic <= 32; harmonic++) {
			wavetable[n] += sinf(2.0 * M_PI * (float)harmonic * (float)n / 
								 (float)wavetable.size()) / (float)harmonic;
		}
	}
	
	// Initialise the wavetable, passing the sample rate and the buffer
	for(unsigned int i = 0; i < 2; i++) {
		gOscillators[i].setup(context->audioSampleRate, wavetable);
	}

	// Set up the oscilloscope
	gScope.setup(2, context->audioSampleRate);
	
	// TODO: initialise the metronome and LED intervals according to sample rate
	
	// Set up the digital pins
	pinMode(context, 0, kLedPin, OUTPUT);

	return true;
}

void render(BelaContext *context, void *userData)
{
    for(unsigned int n = 0; n < context->audioFrames; n++) {
       	// TODO: read the analog input to get the current tempo

    	float out = 0;
    	
    	// Get current frequency based on where we are in the sequencer
    	float midiNote = gSequencerBuffer[gSequencerLocation];
    	float frequency = 440.0 * powf(2.0, (midiNote - 69.0) / 12.0);
    	
    	// Calculate frequences of each of two oscillators
		float frequencies[2];
		frequencies[0] = frequency * (1.0 + kDetune);
		frequencies[1] = frequency * (1.0 - kDetune);

    	for(unsigned int i = 0; i < 2; i++) {
    		gOscillators[i].setFrequency(frequencies[i]);
			out += kAmplitude * gOscillators[i].process();
    	}
    	
    	// TODO: check if enough time has elapsed, and increment
    	// the sequence location if so, looping around when you reach
    	// the end of the sequence

    	// TODO: turn on the LED on if we are early enough in the tick

		// Write the sample to every audio output channel            
    	for(unsigned int channel = 0; channel < context->audioOutChannels; channel++) {
    		audioWrite(context, n, channel, out);
    	}
    	
    	// Convert the MIDI note to a CV based on a 1V/octave standard
    	float octaves = (midiNote - 36.0) / 12.0;
    	float cv = octaves / 5.0;	// 1V per octave; scale is 0-5V
    	
    	if(context->analogOutChannels != 0) {
    		analogWriteOnce(context, n/2, kCVOutPin, cv);
    	}
    	
    	// Write the output to the oscilloscope
    	gScope.log(out, cv);    
    }
}

void cleanup(BelaContext *context, void *userData)
{
	
}
