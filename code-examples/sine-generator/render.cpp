/*
 ____  _____ _        _    
| __ )| ____| |      / \   
|  _ \|  _| | |     / _ \  
| |_) | |___| |___ / ___ \ 
|____/|_____|_____/_/   \_\

The platform for ultra-low latency audio and sensor processing
http://bela.io

(c) 2020 Augmented Instruments Ltd

A project from the Augmented Instruments Laboratory within the
Centre for Digital Music at Queen Mary University of London.
http://instrumentslab.org

The Bela software is distributed under the GNU Lesser General Public License
(LGPL 3.0), available here: https://www.gnu.org/licenses/lgpl-3.0.txt
*/

#include <Bela.h>
#include <cmath>
#include <vector>
#include <libraries/AudioFile/AudioFile.h>	

// This code is NOT real-time. The calculate_sine() function is called
// once at the beginning of the program (in setup()) to generate the whole
// signal at once. The program then plays back the sound that is generated, 
// which is also saved in a WAV file.

float gFrequency = 440.0;	// Frequency of the sine wave in Hz
float gAmplitude = 0.6;		// Amplitude of the sine wave (1.0 is maximum)
float gDuration = 5.0;		// Length of file to generate, in seconds

// Variables related to file I/O for this example
// ----------------------------------------------
std::string gFilename = "output.wav";
std::vector<float> gSampleData;
int gNumSamples = 0;
int gReadPointer = 0;

// This function calculates a sine wave, storing it in a buffer
// of length numSamples.
void calculate_sine(float *buffer, int numSamples, float sampleRate)
{
	// Generate the sine wave sample-by-sample for the whole duration
	for (int n = 0; n < numSamples; n++) {
	    // Calculate one sample of the sine wave
		float out = gAmplitude * sin(2.0 * M_PI * n * gFrequency / sampleRate);
		
		// Store the sample in the buffer
		buffer[n] = out;
	}
}

// setup() runs once at the beginning of your program
bool setup(BelaContext *context, void *userData)
{
	// Calculate number of samples
	float sampleRate = context->audioSampleRate;		// sample rate measured in samples per second
	gNumSamples = gDuration * sampleRate;				// duration times sample rate is the total number of samples

	// Allocate storage for audio
	gSampleData.resize(gNumSamples);					
	
	// Call the code that calculates the sine wave
	calculate_sine(gSampleData.data(), gNumSamples, sampleRate);

    // Write the buffer we just calculated to a WAV file
	AudioFileUtilities::write(gFilename, gSampleData.data(), 1, gNumSamples, sampleRate);

	return true;
}

// render() is called repeatedly by Bela for each audio block
void render(BelaContext *context, void *userData)
{
    for(unsigned int n = 0; n < context->audioFrames; n++) {
        // Increment read pointer and reset to 0 when end of file is reached
        if(++gReadPointer >= gNumSamples)
            gReadPointer = 0;

    	for(unsigned int channel = 0; channel < context->audioOutChannels; channel++) {
			// Write the sample to every audio output channel
    	    float out = gSampleData[gReadPointer];
    		audioWrite(context, n, channel, out);
    	}
    }
}

// cleanup() runs once at the end of the program
void cleanup(BelaContext *context, void *userData)
{
}
