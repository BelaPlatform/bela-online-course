/*
 ____  _____ _        _    
| __ )| ____| |      / \   
|  _ \|  _| | |     / _ \  
| |_) | |___| |___ / ___ \ 
|____/|_____|_____/_/   \_\

http://bela.io

C++ Real-Time Audio Programming with Bela - Lecture 19: Phase vocoder, part 2
fft-sine: display the FFT of a sine wave and calculate its frequency from the FFT
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

// FFT-related variables
Fft gFft;							// FFT processing object
const int gFftSize = 1024;			// FFT window size in samples
const int gHopSize = 128;			// How often we calculate a window

// Circular buffer and pointer for assembling a window of samples
const int gBufferSize = 2*gFftSize;
std::vector<float> gInputBuffer(gBufferSize);
int gInputBufferPointer = 0;
int gHopCounter = 0;

// Thread for FFT processing
AuxiliaryTask gFftTask;
int gCachedInputBufferPointer = 0;

void process_fft_background(void *);

// Sine wave variables
const float kDefaultFrequency = 10.0 * 44100.0 / gFftSize;	// Start with an exact bin frequency
float gFrequency = kDefaultFrequency;
float gPhase = 0.0;

// Bela oscilloscope
Scope gScope;

// GUI to emulate the LEDs
Gui gSpectrumGui;

// When the settings change from the GUI, this function is called
bool guiCallback(JSONObject& json, void*)
{
	// Look for a message to change the oscillator frequency
	std::wstring ws = JSON::s2ws("oscfreq");
	if(json.find(ws) != json.end() && json[ws]->IsNumber()) {
		gFrequency = json[ws]->AsNumber();
	}
	
	return false;
}


bool setup(BelaContext *context, void *userData)
{
	// Set up the FFT and its buffers
	gFft.setup(gFftSize);
	
	// Initialise the oscilloscope
	gScope.setup(1, context->audioSampleRate);
	
	// Set up the GUI
	gSpectrumGui.setup(context->projectName);
	gSpectrumGui.setControlDataCallback(guiCallback, nullptr);
	
	// Set up the thread for the FFT
	gFftTask = Bela_createAuxiliaryTask(process_fft_background, 50, "bela-process-fft");

	return true;
}

// Helper function to wrap the phase between -pi and pi
float wrapPhase(float phaseIn)
{
    if (phaseIn >= 0)
        return fmodf(phaseIn + M_PI, 2.0 * M_PI) - M_PI;
    else
        return fmodf(phaseIn - M_PI, -2.0 * M_PI) + M_PI;	
}

// This function handles the FFT processing in this example once the buffer has
// been assembled.

void process_fft(std::vector<float> const& inBuffer, unsigned int inPointer)
{
	static std::vector<float> unwrappedBuffer(gFftSize);	// Container to hold the unwrapped time-domain values
	static std::vector<float> lastInputPhases(gFftSize);	// Hold the phases from the previous hop of input signal

	// These containers hold the converted representation from magnitude-phase
	// into magnitude-frequency, used for pitch shifting
	// TODO: add a vector to hold calculated frequencies for each bin
	static std::vector<float> analysisMagnitudes(gFftSize / 2 + 1);

	// This array holds other calculations to be sent to the GUI such as detected frequency 
	static std::vector<float> calculationsForGui(2);

	static int guiCounter = 0;	// Used to throttle how often we send the FFT to the GUI	
	int maxBinIndex = 0;		// Index of the bin with peak magnitude
	float maxBinValue = 0;		// Magnitude of the peak bin

	// Copy buffer into FFT input
	for(int n = 0; n < gFftSize; n++) {
		// Use modulo arithmetic to calculate the circular buffer index
		int circularBufferIndex = (inPointer + n - gFftSize + gBufferSize) % gBufferSize;
		unwrappedBuffer[n] = inBuffer[circularBufferIndex];
	}
	
	// Process the FFT based on the time domain input
	gFft.fft(unwrappedBuffer);
		
	// Analyse the lower half of the spectrum. The upper half is just
	// the complex conjugate and does not contain any unique information
	for(int n = 0; n <= gFftSize/2; n++) {
		// Turn real and imaginary components into amplitude and phase
		float amplitude = gFft.fda(n);
		float phase = atan2f(gFft.fdi(n), gFft.fdr(n));
		
		// TODO: calculate the phase difference in this bin between the last
		// hop and this one, which will indirectly give us the exact frequency

		// TODO: subtract the amount of phase increment we'd expect to see based
		// on the centre frequency of this bin (2*pi*n/gFftSize) for this
		// hop size, then wrap to the range -pi to pi
		
		// TODO: find deviation in (fractional) number of bins from the centre frequency

		// TODO: add the original bin number to get the fractional bin where this partial belongs
		
		// Save the magnitude for later and for the GUI
		analysisMagnitudes[n] = amplitude;
		
		// Save the phase for next hop
		lastInputPhases[n] = phase;
		
		// Find the bin with the largest magnitude to display in the GUI
		if(amplitude > maxBinValue) {
			maxBinValue = amplitude;
			maxBinIndex = n;
		}
	}
	
	// Send data to the GUI
	if(++guiCounter >= 8) {
		guiCounter = 0;
		
		// Send the current magnitude spectrum 
		gSpectrumGui.sendBuffer(0, analysisMagnitudes);	
		
		// Send the detected bin number and frequency
		// TODO: change this to display the calculated frequency for maxBinIndex 
		calculationsForGui[0] = maxBinIndex;
		calculationsForGui[1] = maxBinIndex * 44100.0 / gFftSize;
		gSpectrumGui.sendBuffer(1, calculationsForGui);
	}
}

// This function runs in an auxiliary task on Bela, calling process_fft
void process_fft_background(void *)
{
	process_fft(gInputBuffer, gCachedInputBufferPointer);
}

void render(BelaContext *context, void *userData)
{
	for(unsigned int n = 0; n < context->audioFrames; n++) {
        // Generate a sine wave
        float in = 0.5 * sinf(gPhase);
        gPhase += 2.0 * M_PI * gFrequency / context->audioSampleRate;
        if(gPhase >= 2.0 * M_PI)
        	gPhase -= 2.0 * M_PI;

		// Store the sample ("in") in a buffer for the FFT
		// Increment the pointer and when full window has been 
		// assembled, call process_fft()
		gInputBuffer[gInputBufferPointer++] = in;
		if(gInputBufferPointer >= gBufferSize) {
			// Wrap the circular buffer
			// Notice: this is not the condition for starting a new FFT
			gInputBufferPointer = 0;
		}
		
		// Increment the hop counter and start a new FFT if we've reached the hop size
		if(++gHopCounter >= gHopSize) {
			gHopCounter = 0;
			
			gCachedInputBufferPointer = gInputBufferPointer;
			Bela_scheduleAuxiliaryTask(gFftTask);
		}

		// Write the audio to the output
		for(unsigned int channel = 0; channel < context->audioOutChannels; channel++) {
			audioWrite(context, n, channel, in);
		}
		
		// Log to the Scope
		gScope.log(in);
	}
}

void cleanup(BelaContext *context, void *userData)
{

}
