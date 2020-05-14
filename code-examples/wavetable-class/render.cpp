/*
 ____  _____ _        _    
| __ )| ____| |      / \   
|  _ \|  _| | |     / _ \  
| |_) | |___| |___ / ___ \ 
|____/|_____|_____/_/   \_\

http://bela.io

C++ Real-Time Audio Programming with Bela - Lecture 5: Classes and Objects
wavetable-class: an example that implements a wavetable oscillator as a C++ class
*/

#include <Bela.h>
#include <libraries/Gui/Gui.h>
#include <libraries/GuiController/GuiController.h>
#include <cmath>
#include <vector>

#include "wavetable.h"	// This is needed for the Wavetable class

// Browser-based GUI to adjust parameters
Gui gui;
GuiController controller;

// Wavetable oscillator
Wavetable gOscillator;

bool setup(BelaContext *context, void *userData)
{
	std::vector<float> wavetable;
	unsigned int wavetableSize = 512;
		
	// Populate a buffer with a sine wave
	wavetable.resize(wavetableSize);
	for(unsigned int n = 0; n < wavetable.size(); n++) {
		wavetable[n] = sinf(2.0 * M_PI * (float)n / (float)wavetable.size());
	}
	
	// Initialise the wavetable, passing the sample rate and the buffer
	gOscillator.setup(context->audioSampleRate, wavetable);
	
	// Set up the GUI
	gui.setup(context->projectName);
	controller.setup(&gui, "Wavetable Controller");	
	
	// Arguments: name, default value, minimum, maximum, increment
	controller.addSlider("Frequency", 220, 55, 440, 0);
	controller.addSlider("Amplitude (dB)", -20, -40, 0, 0);

	return true;
}

void render(BelaContext *context, void *userData)
{
	float frequency = controller.getSliderValue(0);		// Frequency is first slider
	float amplitudeDB = controller.getSliderValue(1);	// Amplitude is second slider	
	
	float amplitude = powf(10.0, amplitudeDB / 20);		// Convert dB to linear amplitude
	
	gOscillator.setFrequency(frequency);
	
    for(unsigned int n = 0; n < context->audioFrames; n++) {
		float out = amplitude * gOscillator.process();
            
    	for(unsigned int channel = 0; channel < context->audioOutChannels; channel++) {
			// Write the sample to every audio output channel
    		audioWrite(context, n, channel, out);
    	}
    }
}

void cleanup(BelaContext *context, void *userData)
{
	
}
