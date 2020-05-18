/*
 ____  _____ _        _    
| __ )| ____| |      / \   
|  _ \|  _| | |     / _ \  
| |_) | |___| |___ / ___ \ 
|____/|_____|_____/_/   \_\

http://bela.io

C++ Real-Time Audio Programming with Bela - Lecture 6: Analog I/O
vco: a project to be converted from GUI controls into analog input controls
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

bool setup(BelaContext *context, void *userData)
{
	std::vector<float> wavetable;
	
	// Check that we have the expected number of analog inputs and outputs
	// because render() assumes half as many analog frames as audio frames
	if(context->audioFrames != 2*context->analogFrames) {
		rt_fprintf(stderr, "This project needs analog I/O running at half the audio rate.\n");
		return false;
	}
	
	if(context->analogInChannels < 3) {
		rt_fprintf(stderr, "This project needs at least 3 analog inputs.\n");
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
	// TODO: change this code so it uses the analog inputs instead of the
	// GUI sliders for frequency, amplitude and detune ratio
	
	float frequency = gGuiController.getSliderValue(0);		// Frequency is first slider
	float amplitudeDB = gGuiController.getSliderValue(1);	// Amplitude is second slider	
	float detune = gGuiController.getSliderValue(2);		// Detune ratio is third slider
	
	float amplitude = powf(10.0, amplitudeDB / 20);		// Convert dB to linear amplitude
	
	float frequencies[2];
	frequencies[0] = frequency * (1.0 + detune);
	frequencies[1] = frequency * (1.0 - detune);
	
    for(unsigned int n = 0; n < context->audioFrames; n++) {
    	float out = 0;
    	
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
    }
}

void cleanup(BelaContext *context, void *userData)
{
	
}
