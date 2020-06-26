/*
 ____  _____ _        _    
| __ )| ____| |      / \   
|  _ \|  _| | |     / _ \  
| |_) | |___| |___ / ___ \ 
|____/|_____|_____/_/   \_\

http://bela.io

C++ Real-Time Audio Programming with Bela - Lecture 12: Envelopes
*/

// Filter.h: header file for defining a second order resonant kow pass filter

#pragma once

class Filter {

public:
	// Constructor
	Filter();
	
	// Constructor specifying a sample rate
	Filter(float sampleRate);
	
	// Set the sample rate, used for all calculations
	void setSampleRate(float rate);
	
	// Set the frequency and recalculate coefficients
	void setFrequency(float frequency);
	
	// Set the Q and recalculate the coefficients
	void setQ(float q);
	
	// Reset previous history of filter
	void reset();
	
	// Calculate the next sample of output, changing the envelope
	// state as needed
	float process(float input); 
	
	// Destructor
	~Filter();

private:
	// Calculate coefficients
	void calculateCoefficients(float frequency, float q);

	// State variables, not accessible to the outside world
	bool ready_;	// Have the coefficients been calculated?
	float sampleRate_;
	float frequency_;
	float q_;
	float coeffA1_, coeffA2_, coeffB0_, coeffB1_, coeffB2_;
	float lastX_[2];
	float lastY_[2];
};