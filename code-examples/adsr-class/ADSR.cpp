/*
 ____  _____ _        _    
| __ )| ____| |      / \   
|  _ \|  _| | |     / _ \  
| |_) | |___| |___ / ___ \ 
|____/|_____|_____/_/   \_\

http://bela.io

C++ Real-Time Audio Programming with Bela - Lecture 14: ADSR
*/

// ADSR.cpp: implement the ADSR (attack-decay-sustain-release) class

#include "ADSR.h"

// Constructor. Set up some default parameters.
// We can also use initialisation lists before the 
// start of the curly braces to set these values
ADSR::ADSR()
{
	attackTime_ = 0.001;
	decayTime_ = 0.001;
	sustainLevel_ = 1;
	releaseTime_ = 0.001;

	state_ = StateOff;
}

// Set the sample rate, used for all calculations
void ADSR::setSampleRate(float rate) 
{
	ramp_.setSampleRate(rate);
}

// Start the envelope, going to the Attack state
void ADSR::trigger() 
{
	// TODO: go to the Attack state from whichever state we were in
}

// Stop the envelope, going to the Release state
void ADSR::release() 
{
	// TODO: go to the Release state from whichever state we were in
}

// Calculate the next sample of output, changing the envelope
// state as needed
float ADSR::process() 
{
	// Look at the state we're in to decide what value to return. 
	// This function handles the outputs within the state but
	// does not handle the transitions caused by external note events.
	// Those are done in trigger() and release().
	
   	if(state_ == StateOff) {
		// Nothing to do here. trigger() will change the state.
	}
	else if(state_ == StateAttack) {
		// TODO: look for ramp to finish before moving to next phase
	}
	else if(state_ == StateDecay) {
		// TODO: look for ramp to finish before moving to next phase
	}
	else if(state_ == StateSustain) {
		// Nothing to do here. release() will change the state.
	}
	else if(state_ == StateRelease) {
		// TODO: wait until the envelope returns to 0
	}
    	
    // TODO: return the current output level
    return 0;
}

// Indicate whether the envelope is active or not (i.e. in
// anything other than the Off state)
bool ADSR::isActive() 
{
	return (state_ != StateOff);
}

// Methods to set the value of the parameters. We constrain
// each parameter to a sensible range
void ADSR::setAttackTime(float attackTime)
{
	// TODO
}

void ADSR::setDecayTime(float decayTime)
{
	// TODO
}

void ADSR::setSustainLevel(float sustainLevel)
{
	// TODO
}

void ADSR::setReleaseTime(float releaseTime)
{
	// TODO
}

// Destructor
ADSR::~ADSR() 
{
	// Nothing to do here
}