/*
 ____  _____ _        _    
| __ )| ____| |      / \   
|  _ \|  _| | |     / _ \  
| |_) | |___| |___ / ___ \ 
|____/|_____|_____/_/   \_\

http://bela.io

C++ Real-Time Audio Programming with Bela - Lecture 12: Envelopes
*/

// Filter.cpp: implement a second-order lowpass filter of variable frequency and Q

#include <cmath>
#include "Filter.h"

// Constructor
Filter::Filter() : Filter(44100.0) {}

// Constructor specifying a sample rate
Filter::Filter(float sampleRate)
{
	setSampleRate(sampleRate);
	reset();

	// Set some defaults
	frequency_ = 1000.0;
	q_ = 0.707;
	ready_ = false;	// This flag will be set to true when the coefficients are calculated
}
	
// Set the sample rate, used for all calculations
void Filter::setSampleRate(float rate)
{
	sampleRate_ = rate;	
	
	if(ready_)
		calculateCoefficients(frequency_, q_);
}

// Set the frequency and recalculate coefficients
void Filter::setFrequency(float frequency)
{
	frequency_ = frequency;
	calculateCoefficients(frequency_, q_);
}
	
// Set the Q and recalculate the coefficients
void Filter::setQ(float q)
{
	q_ = q;
	calculateCoefficients(frequency_, q_);
}
	
// Calculate coefficients
void Filter::calculateCoefficients(float frequency, float q)
{
	// Helper variables
	float w = frequency * 2.0 * M_PI;
	float t = 1.0 / sampleRate_;

	// Calculate coefficients
	float a0 = 4.0 + ((w/q)*2.0*t) + pow(w, 2.0) * pow(t, 2.0);
	coeffB0_ = coeffB2_ =  pow(w, 2.0) * pow(t, 2.0) / a0;
	coeffB1_ = pow(w, 2.0) * 2.0 * pow(t, 2.0) / a0;
	coeffA1_ = ((2.0 * pow(t, 2.0) * pow(w, 2.0)) -8.0) / a0;
	coeffA2_ = (4.0 - (w/q*2.0*t) + (pow(w, 2.0) * pow(t, 2.0))) / a0;	
	
	ready_ = true;
}
	
// Reset previous history of filter
void Filter::reset()
{
	lastX_[0] = lastX_[1] = 0;
	lastY_[0] = lastY_[1] = 0;
}
	
// Calculate the next sample of output, changing the envelope
// state as needed
float Filter::process(float input)
{
	if(!ready_)
		return input;
		
    float out = input * coeffB0_ + lastX_[0] * coeffB1_ + lastX_[1] * coeffB2_
    			- lastY_[0] * coeffA1_ - lastY_[1] * coeffA2_;
    
    lastX_[1] = lastX_[0];
    lastX_[0] = input;
    lastY_[1] = lastY_[0];
    lastY_[0] = out;
    
    return out;
}
	
// Destructor
Filter::~Filter()
{
	// Nothing to do here
}