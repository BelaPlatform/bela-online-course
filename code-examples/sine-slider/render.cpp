/*
 ____  _____ _        _    
| __ )| ____| |      / \   
|  _ \|  _| | |     / _ \  
| |_) | |___| |___ / ___ \ 
|____/|_____|_____/_/   \_\

http://bela.io

C++ Real-Time Audio Programming with Bela - Lecture 4: Parameter control
sine-slider: oscillator example using a browser-based GUI for control
*/


#include <Bela.h>
#include <libraries/Gui/Gui.h>      				 // Need this to use the GUI
#include <libraries/GuiController/GuiController.h>   // Need this to use the GUI
#include <math.h>

float gPhase = 0;			// Save the phase between calls to render()

// Browser-based GUI to adjust parameters
Gui gui;
GuiController controller;

// setup() only runs one time
bool setup(BelaContext *context, void *userData)
{
	// Set up the GUI
	gui.setup(context->projectName);
	controller.setup(&gui, "Sinetone Controller");
	
	// Arguments: name, default value, minimum, maximum, increment
	controller.addSlider("Frequency", 440, 220, 880, 0);
	controller.addSlider("Amplitude", 0.5, 0, 1, 0);
	
    return true;
}

// render() is called every time there is a new block to calculate
void render(BelaContext *context, void *userData)
{
	float frequency = controller.getSliderValue(0);	// Frequency is first slider
	float amplitude = controller.getSliderValue(1);	// Amplitude is second slider
	
   	// This for() loop goes through all the samples in the block
	for (unsigned int n = 0; n < context->audioFrames; n++) {
	    // Increment the phase by one sample's worth at this frequency
		gPhase += 2.0 * M_PI * frequency / context->audioSampleRate;
		if(gPhase >= 2.0 * M_PI)
			gPhase -= 2.0 * M_PI;

		// Calculate a sample of the sine wave
		float out = amplitude * sin(gPhase);

		// Store the sample in the audio output buffer
		for(unsigned int channel = 0; channel < context->audioOutChannels; channel++) {
		    audioWrite(context, n, channel, out);
		}
    }
}

// cleanup() runs once when the program stops
void cleanup(BelaContext *context, void *userData)
{
	// nothing to do here
}
