/*
 ____  _____ _        _    
| __ )| ____| |      / \   
|  _ \|  _| | |     / _ \  
| |_) | |___| |___ / ___ \ 
|____/|_____|_____/_/   \_\

http://bela.io

C++ Real-Time Audio Programming with Bela - Lecture 4: Parameter control
wavetable-slider: oscillator example using a browser-based GUI for control
*/

#include <Bela.h>
#include <libraries/Gui/Gui.h>
#include <libraries/GuiController/GuiController.h>
#include <cmath>

const int gWavetableLength = 512;	// The length of the buffer in frames
float gWavetable[gWavetableLength];	// Buffer that holds the wavetable
float gReadPointer = 0;				// Position of the last frame we played 

// Browser-based GUI to adjust parameters
Gui gui;
GuiController controller;

bool setup(BelaContext *context, void *userData)
{
	// Generate a sawtooth waveform (a ramp from -1 to 1) and
	// store it in the buffer. Notice: generating the wavetable does 
	// not depend on the audio sample rate (why not?)
	for(unsigned int n = 0; n < gWavetableLength; n++) {
		gWavetable[n] = -1.0 + 2.0 * (float)n / (float)(gWavetableLength - 1);
	}

	// Set up the GUI
	gui.setup(context->projectName);
	controller.setup(&gui, "Wavetable Controller");	
	
	// Arguments: name, default value, minimum, maximum, increment
	controller.addSlider("Frequency", 220, 55, 440, 0);
	controller.addSlider("Amplitude", 0.1, 0, 0.5, 0);

	return true;
}

void render(BelaContext *context, void *userData)
{
	float frequency = controller.getSliderValue(0);	// Frequency is first slider
	float amplitude = controller.getSliderValue(1);	// Amplitude is second slider	
	
    for(unsigned int n = 0; n < context->audioFrames; n++) {
    	// The pointer will take a fractional index. Look for the sample on
    	// either side which are indices we can actually read into the buffer.
    	// If we get to the end of the buffer, wrap around to 0.
    	int indexBelow = floorf(gReadPointer);
    	int indexAbove = indexBelow + 1;
    	if(indexAbove >= gWavetableLength)
    		indexAbove = 0;
    	
    	// For linear interpolation, we need to decide how much to weigh each
    	// sample. The closer the fractional part of the index is to 0, the
    	// more weight we give to the "below" sample. The closer the fractional
    	// part is to 1, the more weight we give to the "above" sample.
    	float fractionAbove = gReadPointer - indexBelow;
    	float fractionBelow = 1.0 - fractionAbove;
    	
    	// Calculate the weighted average of the "below" and "above" samples
        float out = amplitude * (fractionBelow * gWavetable[indexBelow] +
        				fractionAbove * gWavetable[indexAbove]);

        // Increment read pointer and reset to 0 when end of table is reached
        gReadPointer += gWavetableLength * frequency / context->audioSampleRate;
        while(gReadPointer >= gWavetableLength)
            gReadPointer -= gWavetableLength;
            
    	for(unsigned int channel = 0; channel < context->audioOutChannels; channel++) {
			// Write the sample to every audio output channel
    		audioWrite(context, n, channel, out);
    	}
    }
}

void cleanup(BelaContext *context, void *userData)
{

}
