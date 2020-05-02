/*
 ____  _____ _        _    
| __ )| ____| |      / \   
|  _ \|  _| | |     / _ \  
| |_) | |___| |___ / ___ \ 
|____/|_____|_____/_/   \_\

http://bela.io

C++ Real-Time Audio Programming with Bela - Lecture 2: Playing recorded samples
sample-player: partially finished example that plays a 
               recorded sound file in a loop.
*/

#include <Bela.h>
#include <libraries/AudioFile/AudioFile.h>

std::string gFilename = "slow-drum-loop.wav";	// Name of the sound file (in project folder)
std::vector<float> gSampleBuffer;				// Buffer that holds the sound file
int gReadPointer = 0;							// Position of the last frame we played 

bool setup(BelaContext *context, void *userData)
{
	// Load the sample from storage into a buffer	
	gSampleBuffer = AudioFileUtilities::loadMono(gFilename);
	
	// Check if the load succeeded
	if(gSampleBuffer.size() == 0) {
    	rt_printf("Error loading audio file '%s'\n", gFilename.c_str());
    	return false;
	}

    rt_printf("Loaded the audio file '%s' with %d frames (%.1f seconds)\n", 
    			gFilename.c_str(), gSampleBuffer.size(),
    			gSampleBuffer.size() / context->audioSampleRate);

	return true;
}

void render(BelaContext *context, void *userData)
{
    for(unsigned int n = 0; n < context->audioFrames; n++) {
        // TODO: get the next sample from the buffer, then update the read pointer
        // When you reach the end of the buffer, start over again from the beginning.
		// Hint: use gSampleBuffer.size() to find the length of the buffer in samples.
        float out = 0;

    	for(unsigned int channel = 0; channel < context->audioOutChannels; channel++) {
			// Write the sample to every audio output channel
    		audioWrite(context, n, channel, out);
    	}
    }
}

void cleanup(BelaContext *context, void *userData)
{

}
