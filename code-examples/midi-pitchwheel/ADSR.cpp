/*
 ____  _____ _        _    
| __ )| ____| |      / \   
|  _ \|  _| | |     / _ \  
| |_) | |___| |___ / ___ \ 
|____/|_____|_____/_/   \_\

http://bela.io

C++ Real-Time Audio Programming with Bela - Lecture 16: MIDI part 2
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
	// Go to the Attack state from whichever state we were in
	state_ = StateAttack;
	ramp_.rampTo(1.0, attackTime_);
}

// Stop the envelope, going to the Release state
void ADSR::release() 
{
	// Go to the Release state from whichever state we were in
	state_ = StateRelease;
	ramp_.rampTo(0.0, releaseTime_);
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
		// Look for ramp to finish before moving to next phase
		if(ramp_.finished()) {
			state_ = StateDecay;
			ramp_.rampTo(sustainLevel_, decayTime_);
		}
	}
	else if(state_ == StateDecay) {
		// Look for ramp to finish before moving to next phase
		if(ramp_.finished()) {
			state_ = StateSustain;
			// No further ramp to create here: it will hold at a fixed level
		}
	}
	else if(state_ == StateSustain) {
		// Nothing to do here. release() will change the state.
	}
	else if(state_ == StateRelease) {
		// Wait until the envelope returns to 0
		if(ramp_.finished()) {
			state_ = StateOff;
		}
	}
    	
    // Return the current output level
    return ramp_.process();
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
	if(attackTime >= 0)
		attackTime_ = attackTime;
	else
		attackTime_ = 0;
}

void ADSR::setDecayTime(float decayTime)
{
	if(decayTime >= 0)
		decayTime_ = decayTime;
	else
		decayTime_ = 0;
}

void ADSR::setSustainLevel(float sustainLevel)
{
	if(sustainLevel < 0)
		sustainLevel_ = 0;
	else if(sustainLevel > 1)
		sustainLevel_ = 1;
	else
		sustainLevel_ = sustainLevel;
}

void ADSR::setReleaseTime(float releaseTime)
{
	if(releaseTime >= 0)
		releaseTime_ = releaseTime;
	else
		releaseTime_ = 0;
}

// Destructor
ADSR::~ADSR() 
{
	// Nothing to do here
}