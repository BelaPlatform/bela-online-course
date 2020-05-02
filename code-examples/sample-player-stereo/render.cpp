/*
 ____  _____ _        _    
| __ )| ____| |      / \   
|  _ \|  _| | |     / _ \  
| |_) | |___| |___ / ___ \ 
|____/|_____|_____/_/   \_\

http://bela.io

C++ Real-Time Audio Programming with Bela - Lecture 2: Playing recorded samples
sample-player-stereo: partially finished example that plays a 
                      recorded sound file in a loop - multichannel version
*/

#include <Bela.h>
#include <libraries/AudioFile/AudioFile.h>

std::string gFilename = "slow-drum-loop.wav";	// Name of the sound file (in project folder)
std::vector<std::vector<float >> gSampleBuffer;	// Buffer that holds the sound file
int gReadPointer = 0;							// Position of the last frame we played 

bool setup(BelaContext *context, void *userData)
{
	// Load the sample from storage into a buffer
	gSampleBuffer = AudioFileUtilities::load(gFilename);
	
	// Check if the load succeeded
	if(gSampleBuffer.size() == 0) {
    	rt_printf("Error loading audio file '%s'\n", gFilename.c_str());
    	return false;
	}
	
	// Make sure we have at least as many sound file channels as audio
	// output channels, so we don't crash in render(). This check could
	// alternatively be done in render() itself.
	if(gSampleBuffer.size() < context->audioOutChannels) {
		rt_printf("Audio file '%s' has %d channels, but needs at least %d.\n", 
					gFilename.c_str(), gSampleBuffer.size(), context->audioOutChannels);
		return false;
	}

    rt_printf("Loaded the audio file '%s' with %d frames (%.1f seconds) and %d channels\n", 
    			gFilename.c_str(), gSampleBuffer[0].size(),
    			gSampleBuffer[0].size() / context->audioSampleRate,
    			gSampleBuffer.size());

	return true;
}

void render(BelaContext *context, void *userData)
{
    for(unsigned int n = 0; n < context->audioFrames; n++) {
        // TODO 1: update the read pointer here.
        // When you reach the end of the buffer, start over again from the beginning
		// Note: you need a different calculation to find the length of the buffer
		// compared to the sample-player example.
        float out = 0;

    	for(unsigned int channel = 0; channel < context->audioOutChannels; channel++) {
			// TODO 2: you will need to read a different buffer for each channel
			
    		audioWrite(context, n, channel, out);
    	}
    }
}

void cleanup(BelaContext *context, void *userData)
{

}
