/*
 ____  _____ _        _    
| __ )| ____| |      / \   
|  _ \|  _| | |     / _ \  
| |_) | |___| |___ / ___ \ 
|____/|_____|_____/_/   \_\

http://bela.io

C++ Real-Time Audio Programming with Bela - Lecture 14: ADSR
*/

// Debouncer.h: simple class to debounce a button

#pragma once

class Debouncer {
private:
	// State machine states
	enum {
		kStateLow = 0,
		kStateJustHigh,
		kStateHigh,
		kStateJustLow
	};

public:
	// Constructor
	Debouncer();
	
	// Constructor specifying a sample rate
	Debouncer(float sampleRate, float interval);
	
	// Set the sample rate, used for all calculations
	void setup(float sampleRate, float interval);
	
	// Return the debounced state given the raw input
	bool process(bool rawInput);
	
	// Return whether the button is currently high or low
	bool currentValue();
	
	// Destructor
	~Debouncer();

private:
	// State variables, not accessible to the outside world
	int   currentState_;
	int   counter_;
	int   debounceInterval_;
};