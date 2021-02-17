/*
 ____  _____ _        _    
| __ )| ____| |      / \   
|  _ \|  _| | |     / _ \  
| |_) | |___| |___ / ___ \ 
|____/|_____|_____/_/   \_\

http://bela.io

C++ Real-Time Audio Programming with Bela - Lecture 20: Phase vocoder, part 3
fft-robotisation-v2: round the frequency of each component to a multiple of a fundamental frequency
*/

#include <Bela.h>
#include <libraries/Fft/Fft.h>
#include <libraries/Scope/Scope.h>
#include <libraries/Gui/Gui.h>
#include <libraries/GuiController/GuiController.h>
#include <cmath>
#include <cstring>
#include <vector>
#include <algorithm>
#include "MonoFilePlayer.h"

// FFT-related variables
Fft gFft;							// FFT processing object
const int gFftSize = 1024;			// FFT window size in samples
const int gHopSize = 128;			// How often we calculate a window
float gScaleFactor = 0.25;			// How much to scale the output, based on window type and overlap
float gBaseFrequency = 110;			// Fundamental frequency of the robot effect
float gSampleRate = 44100;			// Sample rate (updated in setup())

// Circular buffer and pointer for assembling a window of samples
const int gBufferSize = 16384;
std::vector<float> gInputBuffer;
int gInputBufferPointer = 0;
int gHopCounter = 0;

// Circular buffer for collecting the output of the overlap-add process
std::vector<float> gOutputBuffer;

// Start the write pointer ahead of the read pointer by at least window + hop, with some margin
int gOutputBufferWritePointer = gFftSize + 2*gHopSize;
int gOutputBufferReadPointer = 0;

// Buffer to hold the windows for FFT analysis and synthesis
std::vector<float> gAnalysisWindowBuffer;
std::vector<float> gSynthesisWindowBuffer;

std::vector<float> gBinFrequencies(gFftSize/2 + 1);

// Name of the sound file (in project folder)
std::string gFilename = "voice.wav"; 

// Object that handles playing sound from a buffer
MonoFilePlayer gPlayer;

// Thread for FFT processing
AuxiliaryTask gFftTask;
int gCachedInputBufferPointer = 0;

void process_fft_background(void *);

// Bela oscilloscope
Scope gScope;

// Browser-based GUI to adjust parameters
Gui gGui;
GuiController gGuiController;

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
    			
    // Cache the sample rate for use in process_fft()
    gSampleRate = context->audioSampleRate;
	
	// Set up the FFT and its buffers
	gFft.setup(gFftSize);
	gInputBuffer.resize(gBufferSize);
	gOutputBuffer.resize(gBufferSize);
	
	// Calculate the windows
	gAnalysisWindowBuffer.resize(gFftSize);
	gSynthesisWindowBuffer.resize(gFftSize);
	for(int n = 0; n < gFftSize; n++) {
		// Hann window, split across analysis and synthesis windows
		gAnalysisWindowBuffer[n] = 0.5f * (1.0f - cosf(2.0 * M_PI * n / (float)(gFftSize - 1)));
		gSynthesisWindowBuffer[n] = gAnalysisWindowBuffer[n];
	}
	
	// Precompute the bin frequencies
	for(int n = 0; n <= gFftSize/2; n++) {
		gBinFrequencies[n] = 2.0 * M_PI * (float)n / (float)gFftSize;
	}
	
	// Initialise the oscilloscope
	gScope.setup(2, context->audioSampleRate);
	
	// Set up the GUI
	gGui.setup(context->projectName);
	gGuiController.setup(&gGui, "Robotisation Controller");	
	
	// Arguments: name, minimum, maximum, increment, default value
	gGuiController.addSlider("Frequency", 220, 55.5, 440, 0);
	
	// Set up the thread for the FFT
	gFftTask = Bela_createAuxiliaryTask(process_fft_background, 50, "bela-process-fft");

	return true;
}

// Wrap the phase to the range -pi to pi
float wrapPhase(float phaseIn)
{
    if (phaseIn >= 0)
        return fmodf(phaseIn + M_PI, 2.0 * M_PI) - M_PI;
    else
        return fmodf(phaseIn - M_PI, -2.0 * M_PI) + M_PI;	
}

// This function handles the FFT processing in this example once the buffer has
// been assembled.

void process_fft(std::vector<float> const& inBuffer, unsigned int inPointer, std::vector<float>& outBuffer, unsigned int outPointer)
{
	static std::vector<float> unwrappedBuffer(gFftSize);	// Container to hold the unwrapped time-domain values
	
	static std::vector<float> lastInputPhases(gFftSize);	// Hold the phases from the previous hop of input signal
	static std::vector<float> lastOutputPhases(gFftSize);	// and output (synthesised) signal
	
	// These containers hold the converted representation from magnitude-phase
	// into magnitude-frequency, used for pitch shifting
	static std::vector<float> analysisMagnitudes(gFftSize / 2 + 1);
	static std::vector<float> analysisFrequencies(gFftSize / 2 + 1);
	static std::vector<float> synthesisMagnitudes(gFftSize / 2 + 1);
	static std::vector<float> synthesisFrequencies(gFftSize / 2 + 1);
	static std::vector<int> synthesisCount(gFftSize / 2 + 1);
	
	// Copy buffer into FFT input
	for(int n = 0; n < gFftSize; n++) {
		// Use modulo arithmetic to calculate the circular buffer index
		int circularBufferIndex = (inPointer + n - gFftSize + gBufferSize) % gBufferSize;
		unwrappedBuffer[n] = inBuffer[circularBufferIndex] * gAnalysisWindowBuffer[n];
	}
	
	// Process the FFT based on the time domain input
	gFft.fft(unwrappedBuffer);
		
	// Analyse the lower half of the spectrum. The upper half is just
	// the complex conjugate and does not contain any unique information
	for(int n = 0; n <= gFftSize/2; n++) {
		// Turn real and imaginary components into amplitude and phase
		float amplitude = gFft.fda(n);
		float phase = atan2f(gFft.fdi(n), gFft.fdr(n));
		
		// Calculate the phase difference in this bin between the last
		// hop and this one, which will indirectly give us the exact frequency
		float phaseDiff = phase - lastInputPhases[n];
		
		// Subtract the amount of phase increment we'd expect to see based
		// on the centre frequency of this bin (2*pi*n/gFftSize) for this
		// hop size, then wrap to the range -pi to pi
		phaseDiff = wrapPhase(phaseDiff - gBinFrequencies[n] * gHopSize);
		
		// Find deviation from the centre frequency
		float frequencyDeviation = phaseDiff / (float)gHopSize;
		
		// Add the original bin number to get the fractional bin where this partial belongs
		analysisFrequencies[n] = ((float)n * 2.0 * M_PI / (float)gFftSize) + frequencyDeviation;
		
		// Save the magnitude for later and for the GUI
		analysisMagnitudes[n] = amplitude;
		
		// Save the phase for next hop
		lastInputPhases[n] = phase;
	}	

	// Zero out the synthesis bins, ready for new data
	for(int n = 0; n <= gFftSize/2; n++) {
		synthesisMagnitudes[n] = synthesisFrequencies[n] = synthesisCount[n] = 0;
	}
	
	// Handle the robotisation effect, storing frequencies into new bins
	for(int n = 0; n <= gFftSize/2; n++) {
		// Round the frequency to the nearest multiple of the fundamental

		// TODO 1: Start by calculating which (integer) harmonic is the closest to this frequency
		//         by dividing by the fundamental frequency and rounding

		// TODO 2: if the rounded harmonic is greater than 0, then calculate the new rounded
		//         frequency and find the nearest FFT bin for this new frequency.
		//         Ignore any bins that have shifted above the Nyquist frequency
	}
		
	// Synthesise frequencies into new magnitude and phase values for FFT bins
	for(int n = 0; n <= gFftSize / 2; n++) {
		// Get the fractional offset from the bin centre frequency
		float frequencyDeviation = synthesisFrequencies[n] - ((float)n * 2.0 * M_PI / (float)gFftSize);
		
		// Multiply to get back to a phase value
		float phaseDiff = frequencyDeviation * (float)gHopSize;
		
		// Add the expected phase increment based on the bin centre frequency
		phaseDiff +=  gBinFrequencies[n] * gHopSize;
		
		// Advance the phase from the previous hop
		float outPhase = wrapPhase(lastOutputPhases[n] + phaseDiff);
		
		// Now convert magnitude and phase back to real and imaginary components
		gFft.fdr(n) = synthesisMagnitudes[n] * cosf_neon(outPhase);
		gFft.fdi(n) = synthesisMagnitudes[n] * sinf_neon(outPhase);
		
		// Also store the complex conjugate in the upper half of the spectrum
		if(n > 0 && n < gFftSize / 2) {
			gFft.fdr(gFftSize - n) = gFft.fdr(n);
			gFft.fdi(gFftSize - n) = -gFft.fdi(n);
		}
		
		// Save the phase for the next hop
		lastOutputPhases[n] = outPhase;
	}
		
	// Run the inverse FFT
	gFft.ifft();
	
	// Add timeDomainOut into the output buffer
	for(int n = 0; n < gFftSize; n++) {
		int circularBufferIndex = (outPointer + n - gFftSize + gBufferSize) % gBufferSize;
		outBuffer[circularBufferIndex] += gFft.td(n) * gSynthesisWindowBuffer[n];
	}
}

// This function runs in an auxiliary task on Bela, calling process_fft
void process_fft_background(void *)
{
	process_fft(gInputBuffer, gCachedInputBufferPointer, gOutputBuffer, gOutputBufferWritePointer);

	// Update the output buffer write pointer to start at the next hop
	gOutputBufferWritePointer = (gOutputBufferWritePointer + gHopSize) % gBufferSize;
}

void render(BelaContext *context, void *userData)
{
	// Get the pitch shift in semitones from the GUI slider and convert to ratio
	gBaseFrequency = gGuiController.getSliderValue(0);
	
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
		
		// Scale the output down by the scale factor, compensating for the overlap
		out *= gScaleFactor;
		
		// Increment the read pointer in the output cicular buffer
		gOutputBufferReadPointer++;
		if(gOutputBufferReadPointer >= gBufferSize)
			gOutputBufferReadPointer = 0;
		
		// Increment the hop counter and start a new FFT if we've reached the hop size
		if(++gHopCounter >= gHopSize) {
			gHopCounter = 0;
			
			gCachedInputBufferPointer = gInputBufferPointer;
			Bela_scheduleAuxiliaryTask(gFftTask);
		}

		// Write the audio to the output
		for(unsigned int channel = 0; channel < context->audioOutChannels; channel++) {
			audioWrite(context, n, channel, out);
		}
		
		// Log to the Scope
		gScope.log(in, out);
	}
}

void cleanup(BelaContext *context, void *userData)
{

}
