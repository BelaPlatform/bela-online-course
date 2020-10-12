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

#include "Debouncer.h"

// Constructor
Debouncer::Debouncer()
{
	setup(1, 1);
}

// Constructor specifying a sample rate
Debouncer::Debouncer(float sampleRate, float interval)
{
	setup(sampleRate, interval);
}

// Set the sample rate, used for all calculations
void Debouncer::setup(float sampleRate, float interval)
{
	debounceInterval_ = sampleRate * interval;
	currentState_ = kStateLow;
	counter_ = 0;	
}

// Return the debounced state given the raw input
bool Debouncer::process(bool rawInput)
{
   	// Run the state machine with the current input
   	if(currentState_ == kStateLow) {
   		// Button is low, but look for a high value
   		if(rawInput) {
   			// Found high input: move to just-high state
   			currentState_ = kStateJustHigh;
   			counter_ = 0;
   		}
   	}
   	else if(currentState_ == kStateJustHigh) {
   		// Button was just high, wait for debounce
   		// Run counter, wait for timeout
   		
   		if(++counter_ >= debounceInterval_) {
   			// Timeout: now we can start waiting for the input to go low
   			currentState_ = kStateHigh;
   		}
   	}
   	else if(currentState_ == kStateHigh) {
   		// Button is high, could be low anytime
   		// Input: look for low input
   		
   		if(!rawInput) {
   			currentState_ = kStateJustLow;
   			counter_ = 0;
   		}
   	}
   	else if(currentState_ == kStateJustLow) {
   		// Button was just low, wait for debounce
   		// Run counter, wait for timeout
   		 		
   		if(++counter_ >= debounceInterval_) {
   			// Timeout: now we can start waiting for the input to go high
   			currentState_ = kStateLow;
   		}
   	}	
   	
   	return currentValue();
}

// Return whether the button is currently high or low
bool Debouncer::currentValue()
{
	if(currentState_ == kStateHigh || currentState_ == kStateJustHigh)
		return true;
	return false;
}

// Destructor
Debouncer::~Debouncer()
{
}