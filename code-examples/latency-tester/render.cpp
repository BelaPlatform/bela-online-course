/*
 ____  _____ _        _    
| __ )| ____| |      / \   
|  _ \|  _| | |     / _ \  
| |_) | |___| |___ / ___ \ 
|____/|_____|_____/_/   \_\

http://bela.io

C++ Real-Time Audio Programming with Bela - Lecture 10: Latency
latency-tester-audio: Measures the latency from audio output to audio input
*/

#include <Bela.h>
#include <libraries/Scope/Scope.h>

// Constants that define the program behaviour
const unsigned int kTestsPerSecond = 4;			// How many tests to run per second
const float kPulseLength = .02;					// Length of the output pulse
const float kInputLoThreshold = 0.05;			// Input thresholds: look for an edge
const float kInputHiThreshold = 0.15;			// from below the "lo" to above the "hi"

// Global variables
float gLastInput = 0;							// Previous value of the audio input
unsigned int gTestInterval = 0;					// Samples between successive tests
unsigned int gPulseLength = 0;					// How long is the pulse in samples?
unsigned int gTestCounter = 0;					// How many samples since the last test?
bool gInTest = false;							// Are we running a test?
bool gInputAboveThreshold = false;				// Is the input high or low?

// The Bela oscilloscope
Scope gScope;

bool setup(BelaContext *context, void *userData)
{
	// Initialise the number of samples between successive pulses
	// and the length of the pulse
	gTestInterval = context->audioSampleRate / kTestsPerSecond;
	gPulseLength = context->audioSampleRate * kPulseLength;
	
	// Set up the browser-based oscilloscope
	gScope.setup(2, context->audioSampleRate);
	
	return true;
}

void render(BelaContext *context, void *userData)
{
	// Loop through the number of audio frames
	for(unsigned int n = 0; n < context->audioFrames; n++) {
		float input = 0;
		float output = 0;
		
		// Average the audio inputs
		for(unsigned int ch = 0; ch < context->audioInChannels; ch++) {
			input += fabsf(audioRead(context, n, ch));
		}
		input /= (float)context->audioInChannels;
		
		// TODO 1:
		// Increment gTestCounter, and when it reaches the interval,
		// start a new test by setting gInTest to true
		// Don't forget to reset gTestCounter. If gInTest was *already*
		// true, it means the last test never finished (i.e. timeout,
		// no signal received back)
		
		// If we are counting samples, then look for a rising edge above the threshold
		if(gInTest) {
			if(!gInputAboveThreshold && input >= kInputHiThreshold) {
				// Edge found: stop counting samples	
				gInTest = false;
				gInputAboveThreshold = true;				
				
				// TODO 2: 
				// In this location, gTestCounter holds the total number of elapsed
				// samples since the pulse was generated. Calculate the adjusted latency
				// by subtracting the amount we would expect from Bela's own buffering
				// Calculate adjusted latency by subtracting twice the buffer size
				int normalisedSamples = gTestCounter;
				
				// Print the calculated latency
				rt_printf("Latency: %.2fms (%d samples) --- hardware: %.2fms (%d samples)\n", 
						  1000.0 * gTestCounter / context->audioSampleRate,
						  gTestCounter,
						  1000.0 * normalisedSamples / context->audioSampleRate,
						  normalisedSamples);
			}
			
			// Update the previous input
			gLastInput = input;
		}

		// Generate the pulse if we are still in its window
		if(gTestCounter < gPulseLength) {
			output = 1.0 - (float)gTestCounter / (float)gPulseLength;
		}
		else {
			output = 0.0;
		}
		
		// If the input falls below the lower threshold, set the flag accordingly
		if(input < kInputLoThreshold) {
			gInputAboveThreshold = false;
		}
		
		// Write the output to all the channels
		for(unsigned int ch = 0; ch < context->audioOutChannels; ch++) {
			audioWrite(context, n, ch, output);
		}	
		
		// Log the output and response to the scope
		gScope.log(output, input);
	}
}

void cleanup(BelaContext *context, void *userData)
{

}