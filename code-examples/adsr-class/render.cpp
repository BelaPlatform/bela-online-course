/*
 ____  _____ _        _    
| __ )| ____| |      / \   
|  _ \|  _| | |     / _ \  
| |_) | |___| |___ / ___ \ 
|____/|_____|_____/_/   \_\

http://bela.io

C++ Real-Time Audio Programming with Bela - Lecture 14: ADSR
adsr-class: Attack-Decay-Sustain-Release envelope implemented as a class
*/

#include <Bela.h>
#include <libraries/Gui/Gui.h>
#include <libraries/GuiController/GuiController.h>
#include <libraries/Scope/Scope.h>
#include <cmath>
#include "Wavetable.h"
#include "Ramp.h"
#include "Debouncer.h"
#include "ADSR.h"
#include "Filter.h"

// Pin declarations
const unsigned int kButtonPin = 1;

// Oscillator and Filter objects
Wavetable gOscillator;
Filter gFilter;

// Button debouncer object
Debouncer gDebouncer;

// ADSR objects
ADSR gAmplitudeADSR;
// TODO: add an ADSR to control filter cutoff (also needs code in setup())

// Browser-based GUI to adjust parameters
Gui gGui;
GuiController gGuiController;

// Bela Oscilloscope
Scope gScope;

bool setup(BelaContext *context, void *userData)
{
	std::vector<float> wavetable;
	const unsigned int wavetableSize = 512;
		
	// Populate a buffer with the first 64 harmonics of a sawtooth wave
	wavetable.resize(wavetableSize);
	for(unsigned int n = 0; n < wavetable.size(); n++) {
		wavetable[n] = 0;
		for(unsigned int harmonic = 1; harmonic <= 48; harmonic++) {
			wavetable[n] += 0.5 * sinf(2.0 * M_PI * (float)harmonic * (float)n / 
								 (float)wavetable.size()) / (float)harmonic;
		}
	}
	
	// Initialise the wavetable, passing the sample rate and the buffer
	gOscillator.setup(context->audioSampleRate, wavetable);

	// Initialise the filter
	gFilter.setSampleRate(context->audioSampleRate);

	// Initialise the ADSR objects
	gAmplitudeADSR.setSampleRate(context->audioSampleRate);

	// Initialise the debouncer with 50ms interval
	gDebouncer.setup(context->audioSampleRate, .05);
	
	// Set up the GUI
	gGui.setup(context->projectName);
	gGuiController.setup(&gGui, "ADSR Controller");	
	
	// Arguments: name, minimum, maximum, increment, default value
	gGuiController.addSlider("Frequency", 220, 55, 440, 0);
	gGuiController.addSlider("Amplitude Attack time", 0.01, 0.001, 0.1, 0);
	gGuiController.addSlider("Amplitude Decay time", 0.05, 0.01, 0.3, 0);
	gGuiController.addSlider("Amplitude Sustain level", 0.3, 0, 1, 0);
	gGuiController.addSlider("Amplitude Release time", 0.2, 0.001, 2, 0);
	// TODO: add controls for filter

	// Initialise the scope. TODO: log the filter ADSR as well
	gScope.setup(2, context->audioSampleRate);
	
	return true;
}

void render(BelaContext *context, void *userData)
{
	// Retrieve values from the sliders
	float frequency = gGuiController.getSliderValue(0);
	float ampAttackTime = gGuiController.getSliderValue(1);
	float ampDecayTime = gGuiController.getSliderValue(2);
	float ampSustainLevel = gGuiController.getSliderValue(3);
	float ampReleaseTime = gGuiController.getSliderValue(4);
	// TODO: get filter parameters from GUI
	
	// Set oscillator and ADSR parameters
	gOscillator.setFrequency(frequency);
	gAmplitudeADSR.setAttackTime(ampAttackTime);
	gAmplitudeADSR.setDecayTime(ampDecayTime);
	gAmplitudeADSR.setSustainLevel(ampSustainLevel);
	gAmplitudeADSR.setReleaseTime(ampReleaseTime);
	// TODO: set filter ADSR parameters

    for(unsigned int n = 0; n < context->audioFrames; n++) {
    	// Read the button input: note on is a value of 0
    	int buttonValue = digitalRead(context, n, kButtonPin);
    	
    	// The process() method returns whether the button is high
    	// or low right now, but we are interested in the edges:
    	// falling edge is a press, rising edge is a release
    	gDebouncer.process(buttonValue);

    	if(gDebouncer.fallingEdge()) {
			// TODO: button pressed: trigger envelope(s)
    	}    	
    	if(gDebouncer.risingEdge()) {
			// TODO: button released: release envelope(s)
    	}
 
		// TODO: get the next value from the ADSR envelope
    	float amplitude = 0;
    	
		// TODO: set the filter frequency based on its ADSR
    	
    	// Calculate the output
    	float out = gOscillator.process() * amplitude;
		// TODO: apply the filter
            
    	for(unsigned int channel = 0; channel < context->audioOutChannels; channel++) {
			// Write the sample to every audio output channel
    		audioWrite(context, n, channel, out);
    	}
    	
    	// Log the audio output and the envelope to the scope
    	// TODO: also log the filter ADSR
    	gScope.log(out, amplitude);
    }
}

void cleanup(BelaContext *context, void *userData)
{

}
