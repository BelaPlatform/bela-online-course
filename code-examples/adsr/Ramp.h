/*
 ____  _____ _        _    
| __ )| ____| |      / \   
|  _ \|  _| | |     / _ \  
| |_) | |___| |___ / ___ \ 
|____/|_____|_____/_/   \_\

http://bela.io

C++ Real-Time Audio Programming with Bela - Lecture 14: ADSR
*/

// Ramp.h: header file for defining a second order resonant kow pass filter

#pragma once

class Ramp {

public:
	// Constructor
	Ramp();
	
	// Constructor specifying a sample rate
	Ramp(float sampleRate);
	
	// Set the sample rate, used for all calculations
	void setSampleRate(float rate);
	
	// Jump to a value
	void setValue(float value);
	
	// Ramp to a value over a period of time
	void rampTo(float value, float time);
	
	// Generate and return the next ramp output
	float process();
	
	// Return whether the ramp is finished
	bool finished();
	
	// Destructor
	~Ramp();

private:
	// State variables, not accessible to the outside world
	float sampleRate_;
	float currentValue_;
	float increment_;
	int   counter_;
};