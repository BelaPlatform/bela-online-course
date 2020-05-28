/*
 ____  _____ _        _    
| __ )| ____| |      / \   
|  _ \|  _| | |     / _ \  
| |_) | |___| |___ / ___ \ 
|____/|_____|_____/_/   \_\

http://bela.io

C++ Real-Time Audio Programming with Bela - Lecture 8: Filters
sample-player-filter: template code for implementing digital filters
*/

#include <Bela.h>
#include "MonoFilePlayer.h"

// Name of the sound file (in project folder)
std::string gFilename = "slow-drum-loop.wav";

// Object that handles playing sound from a buffer
MonoFilePlayer gPlayer;

// TODO: declare global variable(s) to keep track of filter state

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

	return true;
}

void render(BelaContext *context, void *userData)
{
    for(unsigned int n = 0; n < context->audioFrames; n++) {
        float in = gPlayer.process();

        // TODO: implement filter equation here
        float out = in;

    	for(unsigned int channel = 0; channel < context->audioOutChannels; channel++) {
			// Write the sample to every audio output channel
    		audioWrite(context, n, channel, out);
    	}
    }
}

void cleanup(BelaContext *context, void *userData)
{

}
