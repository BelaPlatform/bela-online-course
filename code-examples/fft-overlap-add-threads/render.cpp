/*
 ____  _____ _        _    
| __ )| ____| |      / \   
|  _ \|  _| | |     / _ \  
| |_) | |___| |___ / ___ \ 
|____/|_____|_____/_/   \_\

http://bela.io

C++ Real-Time Audio Programming with Bela - Lecture 18: Phase vocoder, part 1
fft-overlap-add-threads: overlap-add framework doing FFT in a low-priority thread
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
int gOutputBufferWritePointer = 2*gHopSize;	// Need one extra hop of latency to run in second thread
int gOutputBufferReadPointer = 0;

// Name of the sound file (in project folder)
std::string gFilename = "drumloop.wav"; 

// Object that handles playing sound from a buffer
MonoFilePlayer gPlayer;

// Bela oscilloscope
Scope gScope;

// Thread for FFT processing
AuxiliaryTask gFftTask;
int gCachedInputBufferPointer = 0;

void process_fft_background(void *);

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
	
	// Set up the FFT and its buffers
	gFft.setup(gFftSize);

	// Initialise the scope
	gScope.setup(2, context->audioSampleRate);
	
	// Set up the thread for the FFT
	gFftTask = Bela_createAuxiliaryTask(process_fft_background, 50, "bela-process-fft");

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

// This function runs in an auxiliary task on Bela, calling process_fft
void process_fft_background(void *)
{
	// TODO: call process_fft() -- what arguments do you need to pass compared to the non-thread version?

	// TODO: update the output buffer write pointer to start at the next hop
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
		
		// Get the output sample from the output buffer
		float out = gOutputBuffer[gOutputBufferReadPointer];
		
		// Then clear the output sample in the buffer so it is ready for the next overlap-add
		gOutputBuffer[gOutputBufferReadPointer] = 0;
		
		// Scale the output down by the overlap factor (e.g. how many windows overlap per sample?)
		out *= (float)gHopSize / (float)gFftSize;
		
		// Increment the read pointer in the output cicular buffer
		gOutputBufferReadPointer++;
		if(gOutputBufferReadPointer >= gBufferSize)
			gOutputBufferReadPointer = 0;
		
		// Increment the hop counter and start a new FFT if we've reached the hop size
		if(++gHopCounter >= gHopSize) {
			gHopCounter = 0;
			
			// TODO: start the FFT thread and pass it the appropriate
			//       data (via global variables)
		}

		// Write the audio input to left channel, output to the right channel, both to the scope
		audioWrite(context, n, 0, in);
		audioWrite(context, n, 1, out);
		gScope.log(in, out);
	}
}

void cleanup(BelaContext *context, void *userData)
{

}
