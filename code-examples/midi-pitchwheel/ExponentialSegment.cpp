/*
 ____  _____ _        _    
| __ )| ____| |      / \   
|  _ \|  _| | |     / _ \  
| |_) | |___| |___ / ___ \ 
|____/|_____|_____/_/   \_\

http://bela.io

C++ Real-Time Audio Programming with Bela - Lecture 16: MIDI part 2
*/

// ExponentialSegment.cpp: an exponential segment generator

#include <cmath>
#include "ExponentialSegment.h"

// Constructor
ExponentialSegment::ExponentialSegment() 
{
	sampleRate_ = 1;
	setValue(0);
}
	
// Constructor specifying a sample rate
ExponentialSegment::ExponentialSegment(float sampleRate) 
{
	sampleRate_ = sampleRate;
	setValue(0);
}
	
// Set the sample rate, used for all calculations
void ExponentialSegment::setSampleRate(float rate)
{
	sampleRate_ = rate;	
}
	
// Jump to a value
void ExponentialSegment::setValue(float value)
{
	currentValue_ = value;
	asymptoteValue_ = targetValue_ = value;
	expValue_ = 0;
	multiplier_ = 0;
}
	
// Ramp to a value over a period of time
void ExponentialSegment::rampTo(float value, float time, float overshootRatio)
{
	// Ramp towards the target value
	targetValue_ = value;
	
	// We need to calculate how far beyond the target to ramp, based on the current
	// value and the overshoot
	float distanceToTarget = targetValue_ - currentValue_;
	asymptoteValue_ = currentValue_ + distanceToTarget * overshootRatio;

	expValue_ = currentValue_ - asymptoteValue_;
	
	// Calculate time constant to reach the target in the specified time
	double tau = -1.0 * time / log(1.0 - 1.0/overshootRatio);
	
	// Calculate the multiplier for each frame
	multiplier_ = pow(exp(-1.0 / tau), 1.0 / sampleRate_);	
}
	
// Generate and return the next ramp output
float ExponentialSegment::process()
{
	currentValue_ = asymptoteValue_ + expValue_;
	
	if(!finished())
		expValue_ *= multiplier_;

	return currentValue_;
}
	
// Return whether the ramp is finished
bool ExponentialSegment::finished()
{
	// Check if we have reached the target. Need to check if we're
	// going upwards or downwards
	if(currentValue_ >= targetValue_ && currentValue_ <= asymptoteValue_)
		return true;
	if(currentValue_ <= targetValue_ && currentValue_ >= asymptoteValue_)
		return true;
	return false;
}	

// Destructor
ExponentialSegment::~ExponentialSegment()
{
}