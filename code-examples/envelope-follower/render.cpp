/*
 ____  _____ _        _    
| __ )| ____| |      / \   
|  _ \|  _| | |     / _ \  
| |_) | |___| |___ / ___ \ 
|____/|_____|_____/_/   \_\

http://bela.io

C++ Real-Time Audio Programming with Bela - Lecture 12: Envelopes
envelope-follower: control the frequency of a resonant filter based on the envelope of a signal
*/

#include <Bela.h>
#include <cmath>
#include <libraries/Gui/Gui.h>
#include <libraries/GuiController/GuiController.h>
#include <libraries/Scope/Scope.h>
#include "MonoFilePlayer.h"
#include "Filter.h"

// Name of the sound file (in project folder)
std::string gFilename = "guitar-loop.wav";

// Object that handles playing sound from a buffer
MonoFilePlayer gPlayer;

// Browser-based GUI to adjust parameters
Gui gGui;
GuiController gGuiController;

// Filter object
Filter gFilter;

// Bela oscilloscope
Scope gScope;

bool setup(BelaContext *context, void *userData)
{
	// Load the audio file
	if(!gPlayer.setup(gFilename)) {
    	rt_printf("Error loading audio file '%s'\n", gFilename.c_str());
    	return false;
	}

	// Print some useful info
    rt_printf("Loaded the audio file '%s' with %d frames (%.1f seconds)\n", 
    			gFilename.c_str(), gPlayer.size(),
    			gPlayer.size() / context->audioSampleRate);
	
	// Initialise the filter
	gFilter.setSampleRate(context->audioSampleRate);
	gFilter.setFrequency(200);
	gFilter.setQ(4.0);

	// Set up the GUI
	gGui.setup(context->projectName);
	gGuiController.setup(&gGui, "Filter Controller");	
	
	// Arguments: name, default value, minimum, maximum, increment
	gGuiController.addSlider("Attack Time", 0.002, 0.001, 0.1, 0);
	gGuiController.addSlider("Decay Time", 0.1, 0.01, 2.0, 0);	
	gGuiController.addSlider("Base Frequency", 200.0, 100.0, 1000.0, 0);
	gGuiController.addSlider("Frequency Sensitivity", 3000.0, 0.0, 10000.0, 0);
	gGuiController.addSlider("Q", 4.0, 0.5, 10, 0);
	
	// Initialise the scope
	gScope.setup(2, context->audioSampleRate);

	return true;
}

void render(BelaContext *context, void *userData)
{
	// Get parameters from the GUI sliders
	float attackTime = gGuiController.getSliderValue(0);
	float decayTime = gGuiController.getSliderValue(1);
	float baseFrequency = gGuiController.getSliderValue(2);	
	float freqSensitivity = gGuiController.getSliderValue(3);
	float q = gGuiController.getSliderValue(4);		
	
	gFilter.setQ(q);	// Q doesn't change based on envelope
	
	// TODO: convert attack and decay times into filter coefficients
	// Important: you may need to use double-precision functions for this
	// (e.g. pow() and not powf())
	
    for(unsigned int n = 0; n < context->audioFrames; n++) {
        // Read input sample
        float in = gPlayer.process();
    	
		// TODO: perform the envelope calculation, using two different
		// filters: one if x[n] > y[n-1], and the other if x[n] <= y[n-1]
    	// Perform the envelope calculation
		float envelopeOutput = 0;
    	
    	// TODO: change this to calculate frequency based on envelope value
    	float frequency = baseFrequency;
      
		// Set the filter frequency and process the sample
		gFilter.setFrequency(frequency);
        float out = 0.2 * gFilter.process(in);
        
    	for(unsigned int channel = 0; channel < context->audioOutChannels; channel++) {
			// Write the sample to every audio output channel
    		audioWrite(context, n, channel, out);
    	}
    	
    	// Log to the oscilloscope
    	gScope.log(in, envelopeOutput);
    }
}

void cleanup(BelaContext *context, void *userData)
{

}
