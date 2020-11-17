/*
 ____  _____ _        _    
| __ )| ____| |      / \   
|  _ \|  _| | |     / _ \  
| |_) | |___| |___ / ___ \ 
|____/|_____|_____/_/   \_\

http://bela.io

C++ Real-Time Audio Programming with Bela - Lecture 18: Phase vocoder, part 1
fft-overlap-add: template for implementing phase vocoder effects with overlap-add process
*/

#include <Bela.h>
#include <libraries/Fft/Fft.h>
#include <libraries/Scope/Scope.h>
#include <cmath>
#include <cstring>
#include <vector>
#include <algorithm>
#include "MonoFilePlayer.h"

// FFT-related variables
Fft gFft;					// FFT processing object
const int gFftSize = 1024;	// FFT window size in samples
const int gHopSize = 256;	// How often we calculate a window

// Circular buffer and pointer for assembling a window of samples
const int gBufferSize = 16384;
std::vector<float> gInputBuffer(gBufferSize);
int gInputBufferPointer = 0;
int gHopCounter = 0;

// Circular buffer for collecting the output of the overlap-add process
std::vector<float> gOutputBuffer(gBufferSize);
int gOutputBufferWritePointer = gHopSize;		// At minimum, write pointer stays one hop ahead of read pointer
int gOutputBufferReadPointer = 0;

// Name of the sound file (in project folder)
std::string gFilename = "drumloop.wav"; 

// Object that handles playing sound from a buffer
MonoFilePlayer gPlayer;

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
	
	// Set up the FFT
	gFft.setup(gFftSize);
	
	// Initialise the scope
	gScope.setup(2, context->audioSampleRate);
	
	return true;
}

// This function handles the FFT processing in this example once the buffer has
// been assembled.

void process_fft(std::vector<float> const& inBuffer, unsigned int inPointer, std::vector<float>& outBuffer, unsigned int outPointer)
{
	static std::vector<float> unwrappedBuffer(gFftSize);	// Container to hold the unwrapped values
	
	// Copy buffer into FFT input, starting one window ago
	for(int n = 0; n < gFftSize; n++) {
		// Use modulo arithmetic to calculate the circular buffer index
		int circularBufferIndex = (inPointer + n - gFftSize + gBufferSize) % gBufferSize;
		unwrappedBuffer[n] = inBuffer[circularBufferIndex];
	}
	
	// Process the FFT based on the time domain input
	gFft.fft(unwrappedBuffer); 
		
	// Robotise the output
	// for(int n = 0; n < gFftSize; n++) {
	// 	float amplitude = gFft.fda(n);
	// 	gFft.fdr(n) = amplitude;
	// 	gFft.fdi(n) = 0;
	// }
		
	// Run the inverse FFT
	gFft.ifft();
	
	// Add timeDomainOut into the output buffer starting at the write pointer
	for(int n = 0; n < gFftSize; n++) {
		int circularBufferIndex = (outPointer + n) % gBufferSize;
		outBuffer[circularBufferIndex] += gFft.td(n);
	}
}

void render(BelaContext *context, void *userData)
{
	for(unsigned int n = 0; n < context->audioFrames; n++) {
        // Read the next sample from the buffer
        float in = gPlayer.process();

		// Store the sample ("in") in a buffer for the FFT
		// Increment the pointer and when full window has been 
		// assembled, call process_fft()
		gInputBuffer[gInputBufferPointer++] = in;
		if(gInputBufferPointer >= gBufferSize) {
			// Wrap the circular buffer
			// Notice: this is not the condition for starting a new FFT
			gInputBufferPointer = 0;
		}
		
		// TODO: get the output sample from the output buffer
		float out = 0;
		
		// TODO: then clear the output sample in the buffer so it is ready for the next overlap-add

		// Scale the output down by the overlap factor (e.g. how many windows overlap per sample?)
		out *= (float)gHopSize / (float)gFftSize;
		
		// TODO: increment the read pointer in the output cicular buffer
		// TODO: increment the hop counter and start a new FFT if we've reached the hop size
		//       to start a new FFT, call process_fft(). The first three arguments are:
		//       gInputBuffer, gInputBufferPointer, gOutputBuffer.... what's the fourth one?
		//       Update the output buffer write pointer once the FFT is done (by how much?)

		// Write the audio input to left channel, output to the right channel, both to the scope
		audioWrite(context, n, 0, in);
		audioWrite(context, n, 1, out);
		gScope.log(in, out);
	}
}

void cleanup(BelaContext *context, void *userData)
{

}
