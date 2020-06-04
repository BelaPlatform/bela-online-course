/*
 ____  _____ _        _    
| __ )| ____| |      / \   
|  _ \|  _| | |     / _ \  
| |_) | |___| |___ / ___ \ 
|____/|_____|_____/_/   \_\

http://bela.io

C++ Real-Time Audio Programming with Bela - Lecture 8: Filters
*/

// This is a simple class encapsulating the playback of a sound
// loaded from an audio file. It offers basic controls to loop, start
// and stop the playback. It assumes a mono audio file.

#pragma once

#include <vector>
#include <string>

class MonoFilePlayer {
public:
	// Constructors: the one with arguments automatically calls setup()
	MonoFilePlayer() {}
	MonoFilePlayer(const std::string& filename, bool loop = true, bool autostart = true);
	
	// Load an audio file from the given filename. Returns true on success.
	bool setup(const std::string& filename, bool loop = true, bool autostart = true);
	
	// Start or stop the playback
	void trigger();
	void stop() { isPlaying_ = false; }

	// Return the length of the buffer in samples
	unsigned int size() { return sampleBuffer_.size(); }
	
	// Return the next sample of the loaded audio file
	float process();
	
	// Destructor
	~MonoFilePlayer() {}
	
private:
	std::vector<float> sampleBuffer_;			// Buffer that holds the sound file
	int readPointer_ = 0;						// Position of the last frame we played 
	bool loop_ = false;							// Whether the playback loops at the end
	bool isPlaying_ = false;					// Whether we are currently playing
};

