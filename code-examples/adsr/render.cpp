/*
 ____  _____ _        _    
| __ )| ____| |      / \   
|  _ \|  _| | |     / _ \  
| |_) | |___| |___ / ___ \ 
|____/|_____|_____/_/   \_\

http://bela.io

C++ Real-Time Audio Programming with Bela - Lecture 14: ADSR
adsr: Attack-Decay-Sustain-Release envelope controlled by a button
*/

#include <Bela.h>
#include <libraries/Gui/Gui.h>
#include <libraries/GuiController/GuiController.h>
#include <libraries/Scope/Scope.h>
#include <cmath>
#include "Wavetable.h"
#include "Ramp.h"
#include "Debouncer.h"

// Pin declarations
const unsigned int kButtonPin = 1;

// Oscillator and Ramp objects
Wavetable gOscillator;
Ramp gRamp;

// Button debouncer object
Debouncer gDebouncer;

// Browser-based GUI to adjust parameters
Gui gGui;
GuiController gGuiController;

// Bela Oscilloscope
Scope gScope;

// ADSR state machine variables
enum {
	kADSRStateOff = 0,
	kADSRStateAttack,
	kADSRStateDecay,
	kADSRStateSustain,
	kADSRStateRelease
};

int gADSRState = kADSRStateOff;		// Which state we're in

bool setup(BelaContext *context, void *userData)
{
	std::vector<float> wavetable;
	const unsigned int wavetableSize = 512;
		
	// Populate a buffer with the first 64 harmonics of a sawtooth wave
	wavetable.resize(wavetableSize);
	for(unsigned int n = 0; n < wavetable.size(); n++) {
		wavetable[n] = 0;
		for(unsigned int harmonic = 1; harmonic <= 48; harmonic++) {
			wavetable[n] += sinf(2.0 * M_PI * (float)harmonic * (float)n / 
								 (float)wavetable.size()) / (float)harmonic;
		}
	}
	
	// Initialise the wavetable, passing the sample rate and the buffer
	gOscillator.setup(context->audioSampleRate, wavetable);

	// Initialise the line segment object
	gRamp.setSampleRate(context->audioSampleRate);
	gRamp.setValue(0);
	
	// Initialise the debouncer with 50ms interval
	gDebouncer.setup(context->audioSampleRate, .05);
	
	// Set up the GUI
	gGui.setup(context->projectName);
	gGuiController.setup(&gGui, "ADSR Controller");	
	
	// Arguments: name, minimum, maximum, increment, default value
	gGuiController.addSlider("Frequency", 220, 55, 440, 0);
	gGuiController.addSlider("Attack time", 0.01, 0.001, 0.1, 0);
	gGuiController.addSlider("Decay time", 0.05, 0.01, 0.3, 0);
	gGuiController.addSlider("Sustain level", 0.3, 0, 1, 0);
	gGuiController.addSlider("Release time", 0.2, 0.001, 2, 0);

	// Initialise the scope
	gScope.setup(2, context->audioSampleRate);
	
	return true;
}

void render(BelaContext *context, void *userData)
{
	// Retrieve values from the sliders
	float frequency = gGuiController.getSliderValue(0);
	float attackTime = gGuiController.getSliderValue(1);
	float decayTime = gGuiController.getSliderValue(2);
	float sustainLevel = gGuiController.getSliderValue(3);
	float releaseTime = gGuiController.getSliderValue(4);
	
	gOscillator.setFrequency(frequency);

    for(unsigned int n = 0; n < context->audioFrames; n++) {
    	// Read the button input: note on is a value of 0
    	int buttonValue = digitalRead(context, n, kButtonPin);
    	int noteOn = !gDebouncer.process(buttonValue);
    	
    	if(gADSRState == kADSRStateOff) {
    		// TODO: look for note on to go to attack state
    	}
    	else if(gADSRState == kADSRStateAttack) {
			// TODO: look for ramp to finish before moving to next phase

    	}
    	else if(gADSRState == kADSRStateDecay) {
			// TODO: look for ramp to finish before moving to next phase
    	}
    	else if(gADSRState == kADSRStateSustain) {
    		// TODO: wait until we get a note off
    	}
    	else if(gADSRState == kADSRStateRelease) {
    		// TODO: wait until the envelope returns to 0
			// TODO: allow retriggering back to Attack state
    	}

  		// TODO: store the output of the ADSR envelope into the following variable
    	float amplitude = 0;
    	
    	float out = gOscillator.process() * amplitude;
            
    	for(unsigned int channel = 0; channel < context->audioOutChannels; channel++) {
			// Write the sample to every audio output channel
    		audioWrite(context, n, channel, out);
    	}
    	
    	// Log the audio output and the envelope to the scope
    	gScope.log(out, amplitude);
    }
}

void cleanup(BelaContext *context, void *userData)
{

}
