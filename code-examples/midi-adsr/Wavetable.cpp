/*
 ____  _____ _        _    
| __ )| ____| |      / \   
|  _ \|  _| | |     / _ \  
| |_) | |___| |___ / ___ \ 
|____/|_____|_____/_/   \_\

http://bela.io

C++ Real-Time Audio Programming with Bela - Lecture 15: MIDI part 1
*/

// Wavetable.cpp: file for implementing the wavetable oscillator class

#include <cmath>
#include "Wavetable.h"

// Constructor taking arguments for sample rate and table data
Wavetable::Wavetable(float sampleRate, std::vector<float>& table, bool useInterpolation) {
	setup(sampleRate, table, useInterpolation);
} 

void Wavetable::setup(float sampleRate, std::vector<float>& table, bool useInterpolation)
{
	// It's faster to multiply than to divide on most platforms, so we save the inverse
	// of the sample rate for use in the phase calculation later
	inverseSampleRate_ = 1.0 / sampleRate;

	// Copy other parameters
	table_ = table;
	useInterpolation_ = useInterpolation;
	
	// Initialise the starting state
	readPointer_ = 0;
}

// Set the oscillator frequency
void Wavetable::setFrequency(float f) {
	frequency_ = f;
}

// Get the oscillator frequency
float Wavetable::getFrequency() {
	return frequency_;
}			
	
// Get the next sample and update the phase
float Wavetable::process() {
	float out = 0;
	
	// Make sure we have a valid table
	if(table_.size() == 0)
		return out;
	
	// Increment and wrap the phase
	readPointer_ += table_.size() * frequency_ * inverseSampleRate_;
	while(readPointer_ >= table_.size())
		readPointer_ -= table_.size();
	
	if(useInterpolation_) {
		// The pointer will take a fractional index. Look for the sample on
		// either side which are indices we can actually read into the buffer.
		// If we get to the end of the buffer, wrap around to 0.
		int indexBelow = floorf(readPointer_);
		int indexAbove = indexBelow + 1;
		if(indexAbove >= table_.size())
			indexAbove = 0;
	
		// For linear interpolation, we need to decide how much to weigh each
		// sample. The closer the fractional part of the index is to 0, the
		// more weight we give to the "below" sample. The closer the fractional
		// part is to 1, the more weight we give to the "above" sample.
		float fractionAbove = readPointer_ - indexBelow;
		float fractionBelow = 1.0 - fractionAbove;
	
		// Calculate the weighted average of the "below" and "above" samples
	    out = fractionBelow * table_[indexBelow] +
	    	  fractionAbove * table_[indexAbove];
	}
	else {
		// Read the table without interpolation
		out = table_[(int)readPointer_];
	}
	
	return out;
}			