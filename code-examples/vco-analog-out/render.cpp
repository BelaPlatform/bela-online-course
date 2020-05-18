/*
 ____  _____ _        _    
| __ )| ____| |      / \   
|  _ \|  _| | |     / _ \  
| |_) | |___| |___ / ___ \ 
|____/|_____|_____/_/   \_\

http://bela.io

C++ Real-Time Audio Programming with Bela - Lecture 6: Analog I/O
vco-analog-out: a project which shows the beat frequencies between two
                detuned oscillators on an LED hooked up to the Bela
                analog out. Code exercise is to complete render().
*/

#include <Bela.h>
#include <libraries/Gui/Gui.h>
#include <libraries/GuiController/GuiController.h>
#include <libraries/Scope/Scope.h>
#include <cmath>
#include <vector>

#include "wavetable.h"	// This is needed for the Wavetable class

// Constants that define the program behaviour
const unsigned int kWavetableSize = 512;

// Browser-based GUI to adjust parameters
Gui gGui;
GuiController gGuiController;

// Browser-based oscilloscope
Scope gScope;

// Wavetable oscillator
Wavetable gOscillators[2];

// Wavetable for the LFO
Wavetable gLFO;

bool setup(BelaContext *context, void *userData)
{
	std::vector<float> wavetable;
		
	// Check that we have the expected number of analog inputs and outputs
	// because render() assumes half as many analog frames as audio frames
	if(context->audioFrames != 2*context->analogFrames) {
		rt_fprintf(stderr, "This project needs analog I/O running at half the audio rate.\n");
		return false;
	}
	
	if(context->analogOutChannels == 0) {
		rt_fprintf(stderr, "This project needs analog output to run.\n");
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
	
	// Repopulate the wavetable with a sine wave, scaled to an appropriate
	// range for the LED (analog output is 0 to 1)
	for(unsigned int n = 0; n < wavetable.size(); n++) {
		float minimum = (1.5 / 5.0);
		wavetable[n] = minimum + (1.0 - minimum) * 0.5 * 
								 (1.0 + sinf(2.0 * M_PI * (float)n / (float)wavetable.size()));	
	}
	gLFO.setup(context->audioSampleRate, wavetable);
	
	// Set up the GUI
	gGui.setup(context->projectName);
	gGuiController.setup(&gGui, "Wavetable Controller");	
	
	// Arguments: name, default value, minimum, maximum, increment
	gGuiController.addSlider("Frequency", 220, 55, 440, 0);
	gGuiController.addSlider("Amplitude (dB)", -20, -40, -6, 0);
	gGuiController.addSlider("Detune", 0, 0, 0.05, 0);

	// Set up the oscilloscope
	gScope.setup(1, context->audioSampleRate);

	return true;
}

void render(BelaContext *context, void *userData)
{
    for(unsigned int n = 0; n < context->audioFrames; n++) {
    	float out = 0;
    	
    	// Read the three analog inputs
    	float input0 = analogRead(context, n/2, 0);
    	float input1 = analogRead(context, n/2, 1);
    	float input2 = analogRead(context, n/2, 2);
    	
    	// Rescale their ranges to match the GUI sliders
    	float frequency = 55.0 * powf(2.0, input0 * 4.096);
    	float amplitudeDB = map(input1, 0, 3.3 / 4.096, -80, -6);
    	float detune = map(input2, 0, 3.3 / 4.096, 0, .05);
    	
    	float amplitude = powf(10.0, amplitudeDB / 20);		// Convert dB to linear amplitude
	
		float frequencies[2];
		frequencies[0] = frequency * (1.0 + detune);
		frequencies[1] = frequency * (1.0 - detune);
		
		// TODO 1: calculate the LFO frequency as the difference of the detuned oscillators

    	for(unsigned int i = 0; i < 2; i++) {
    		gOscillators[i].setFrequency(frequencies[i]);
			out += amplitude * gOscillators[i].process();
    	}
            
    	for(unsigned int channel = 0; channel < context->audioOutChannels; channel++) {
			// Write the sample to every audio output channel
    		audioWrite(context, n, channel, out);
    	}
    	
    	// Write the output to the oscilloscope
    	gScope.log(out);    
 
		// TODO 2: calculate the LFO value and write it to the analog output
    }
}

void cleanup(BelaContext *context, void *userData)
{
	
}
