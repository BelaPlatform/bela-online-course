/*
 ____  _____ _        _    
| __ )| ____| |      / \   
|  _ \|  _| | |     / _ \  
| |_) | |___| |___ / ___ \ 
|____/|_____|_____/_/   \_\

http://bela.io

C++ Real-Time Audio Programming with Bela - Lecture 5: Classes and Objects
additive-synth: an example implementing an additive synthesiser based on an
                array of Wavetable oscillator objects
*/

#include <Bela.h>
#include <libraries/Gui/Gui.h>
#include <libraries/GuiController/GuiController.h>
#include <libraries/Scope/Scope.h>
#include <cmath>
#include <vector>
#include <sstream>

#include "wavetable.h"	// This is needed for the Wavetable class

// Constants that define the program behaviour
const unsigned int kWavetableSize = 512;
const unsigned int kNumOscillators = 24;

// Browser-based GUI to adjust parameters
Gui gGui;
GuiController gGuiController;

// Browser-based oscilloscope
Scope gScope;

// Oscillators for the additive synths
std::vector<Wavetable> gOscillators;
std::vector<float> gAmplitudes;

bool setup(BelaContext *context, void *userData)
{
	std::vector<float> wavetable;
		
	// Populate a buffer with a sine wave
	wavetable.resize(kWavetableSize);
	for(unsigned int n = 0; n < wavetable.size(); n++) {
		wavetable[n] = sinf(2.0 * M_PI * (float)n / (float)wavetable.size());
	}
	
	// Create an array of oscillators
	for(unsigned int n = 0; n < kNumOscillators; n++) {
		Wavetable oscillator(context->audioSampleRate, wavetable, false);
		gOscillators.push_back(oscillator);
	}
	
	// Prepare the amplitude buffer
	gAmplitudes.resize(kNumOscillators);
	
	// Set up the GUI
	gGui.setup(context->projectName);
	gGuiController.setup(&gGui, "Wavetable Controller");	
	
	// Arguments: name, default value, minimum, maximum, increment
	gGuiController.addSlider("MIDI note", 60, 36, 96, 1);
	gGuiController.addSlider("Amplitude (dB)", -20, -40, 0, 0);
	
	// Add levels for the individual oscillators
	gGuiController.addSlider("Harmonic 1", 0, -60, 0, 0);
	for(unsigned int n = 1; n < kNumOscillators; n++) {
		std::stringstream name;
		name << "Harmonic " << (n + 1);	// Format the name of the slider
		
		float dBvalue = -60;			// Calculate the default amplitude
		if((n % 2) == 0) {				// based on a square wave
			dBvalue = 20.0 * log10f(1.0 / (float)(n + 1));
		}
		gGuiController.addSlider(name.str(), dBvalue, -60, 0, 0);
	}
	
	// Set up the oscilloscope
	gScope.setup(1, context->audioSampleRate);

	return true;
}

void render(BelaContext *context, void *userData)
{
	float midiNote = gGuiController.getSliderValue(0);		// MIDI note is first slider
	float amplitudeDB = gGuiController.getSliderValue(1);	// Amplitude is second slider	
	
	float frequency = 440.0 * powf(2.0, (midiNote - 69.0) / 12.0);	// MIDI to frequency
	float amplitude = powf(10.0, amplitudeDB / 20);		// Convert dB to linear amplitude
	
	for(unsigned int i = 0; i < gOscillators.size(); i++) {
		// TODO 1:
		// Set the frequency of this oscillator as a multiple of the fundamental frequency
		// Get the amplitude of this oscillator from the slider and store in gAmplitudes[i]
	}
	
    for(unsigned int n = 0; n < context->audioFrames; n++) {
		float out = 0;
		
		// TODO 2: step through all the oscillators in the array and mix
		// their outputs together, weighted by gAmplitudes
		
		// Scale global amplitude
		out *= amplitude;
            
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
