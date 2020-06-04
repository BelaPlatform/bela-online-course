/*
 ____  _____ _        _    
| __ )| ____| |      / \   
|  _ \|  _| | |     / _ \  
| |_) | |___| |___ / ___ \ 
|____/|_____|_____/_/   \_\

http://bela.io

C++ Real-Time Audio Programming with Bela - Lecture 9: Timing
metronome: generate clicks at a regular interval to demonstrate counting time with sampled audio
*/

#include <Bela.h>
#include "MonoFilePlayer.h"

const std::string gFilename = "click.wav";	// Name of the sound file (in project folder)
float gAmplitude = 0.3;						// Volume of the output
MonoFilePlayer gPlayer;						// File playback object

// TODO: declare any needed global variables here

bool setup(BelaContext *context, void *userData)
{
	// Load the audio file; don't play in a loop and don't autostart
	if(!gPlayer.setup(gFilename, false, false)) {
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
		// TODO: check if enough time has elapsed, then call gPlayer.trigger()
		// to start the sound playing if so. You'll need a global variable to count
		// elapsed samples.
		
    	// -- code below this point doesn't need to change --
    	// Get the next sample of the file if it's playing (out = 0 otherwise)
    	float out = gAmplitude * gPlayer.process();
        	
    	for(unsigned int channel = 0; channel < context->audioOutChannels; channel++) {
			// Write the sample to every audio output channel
    		audioWrite(context, n, channel, out);
    	}
    }
}

void cleanup(BelaContext *context, void *userData)
{

}
