/*
 ____  _____ _        _    
| __ )| ____| |      / \   
|  _ \|  _| | |     / _ \  
| |_) | |___| |___ / ___ \ 
|____/|_____|_____/_/   \_\

http://bela.io

C++ Real-Time Audio Programming with Bela - Lecture 12: Envelopes
*/

// Ramp.cpp: a simple line segment generator

#include <cmath>
#include "Ramp.h"

// Constructor
Ramp::Ramp() 
{
	currentValue_ = 0;
	increment_ = 0;
	counter_ = 0;
	sampleRate_ = 1;
}
	
// Constructor specifying a sample rate
Ramp::Ramp(float sampleRate) 
{
	currentValue_ = 0;
	increment_ = 0;
	counter_ = 0;
	sampleRate_ = sampleRate;
}
	
// Set the sample rate, used for all calculations
void Ramp::setSampleRate(float rate)
{
	sampleRate_ = rate;	
}
	
// Jump to a value
void Ramp::setValue(float value)
{
	// TODO: set the value, no increment or counter
}
	
// Ramp to a value over a period of time
void Ramp::rampTo(float value, float time)
{
	// TODO: calculate the increment to get from the current value to the target
	// in the specified amount of time. Don't forget to set the counter.
}
	
// Generate and return the next ramp output
float Ramp::process()
{
	// TODO: increment the value if the counter hasn't reached 0. Return the value.
	return 0;
}
	
// Return whether the ramp is finished
bool Ramp::finished()
{
	// TODO: the ramp is finished when the counter has counted down to 0
	return false;
}	

// Destructor
Ramp::~Ramp()
{
}