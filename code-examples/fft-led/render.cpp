/*
 ____  _____ _        _    
| __ )| ____| |      / \   
|  _ \|  _| | |     / _ \  
| |_) | |___| |___ / ___ \ 
|____/|_____|_____/_/   \_\

http://bela.io

C++ Real-Time Audio Programming with Bela - Lecture 17: Block-based processing
fft-led: blink LEDs in response to frequency content of a signal
*/

#include <Bela.h>
#include <libraries/Fft/Fft.h>
#include <libraries/Gui/Gui.h>
#include <cmath>
#include <cstring>
#include <vector>
#include "MonoFilePlayer.h"

// FFT-related variables
Fft gFft;					// FFT processing object
const int gFftSize = 1024;	// FFT size in samples
float gLoThreshold = 10.0;	// Thresholds used for LEDs
float gHiThreshold = 0.1;
float gLoHiRatio = 0.1;

// GPIO pins and values
const int gOutputPinLo = 0, gOutputPinHi = 1;
int gLedLoOutput = LOW, gLedHiOutput = LOW;

// Name of the sound file (in project folder)
std::string gFilename = "drumloop.wav"; 

// Object that handles playing sound from a buffer
MonoFilePlayer gPlayer;

// GUI to simulate two LEDs
Gui gLedGui;
int gGuiUpdateCounter = 0;
int gGuiBuffer[2] = {0, 0};

// TODO: declare variables for buffer and pointer for 
// assembling a window of samples. If you use a vector for
// the buffer, you'll need set its size inside setup()

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
	
	// Set up the FFT and its input buffer
	gFft.setup(gFftSize);

	// LED pins
	pinMode(context, 0, gOutputPinLo, OUTPUT);
	pinMode(context, 0, gOutputPinHi, OUTPUT);
	
	// GUI to emulate the LEDs
	gLedGui.setup(context->projectName);

	return true;
}

// This function handles the FFT processing in this example once the buffer has
// been assembled.
void process_fft(std::vector<float> const& buffer)
{
	// Process the FFT based on the time domain input
	gFft.fft(buffer);

	// Calculate amount of energy in a range of low and high frequency bins
	float energyLo = 0;
	float energyHi = 0;

	for(int n = 0; n < gFftSize / 32; n++) {
		energyLo += gFft.fda(n);
	}
	energyLo /= (float)(gFftSize / 32);
	
	for(int n = gFftSize/2 - gFftSize/4; n < gFftSize / 2; n++) {
		energyHi += gFft.fda(n);
	}
	energyHi /= (float)(gFftSize / 4);

	// Check if the low-frequency energy exceeds a threshold
	if(energyLo > gLoThreshold)
		gLedLoOutput = HIGH;
	else
		gLedLoOutput = LOW;

	// Check if the high energy exceeds a threshold, independently of the low-frequency energy
	if(energyHi > gHiThreshold && energyHi / energyLo > gLoHiRatio)
		gLedHiOutput = HIGH;
	else
		gLedHiOutput = LOW;
		
	// Uncomment to print the energy levels in low and high frequencies:
	// rt_printf("%f %f %f\n", energyLo, energyHi, energyHi / energyLo);
}

void render(BelaContext *context, void *userData)
{
	for(unsigned int n = 0; n < context->audioFrames; n++) {
        // Read the next sample from the buffer
        float in = gPlayer.process();

		// TODO: store the sample ("in") in a buffer for the FFT
		// Increment the pointer and when full window has been 
		// assembled, call process_fft()
		
		// Flash the LEDs -- values calculated in process_fft()
		digitalWrite(context, n, gOutputPinLo, gLedLoOutput);
		digitalWrite(context, n, gOutputPinHi, gLedHiOutput);

		// Write the audio to the output
		for(unsigned int channel = 0; channel < context->audioOutChannels; channel++) {
			audioWrite(context, n, channel, in);
		}
		
		// Update the Bela GUI at a 100Hz frame rate
		if(++gGuiUpdateCounter >= context->audioSampleRate / 100) {
			gGuiUpdateCounter = 0;
			
			// Send low and high values in two slots of the buffer
			gGuiBuffer[0] = gLedLoOutput;
			gGuiBuffer[1] = gLedHiOutput;
			if(gLedGui.isConnected()) {
				gLedGui.sendBuffer(0, gGuiBuffer);
			}
		}
	}
}

void cleanup(BelaContext *context, void *userData)
{

}
