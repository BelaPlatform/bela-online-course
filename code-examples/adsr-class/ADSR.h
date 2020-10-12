/*
 ____  _____ _        _    
| __ )| ____| |      / \   
|  _ \|  _| | |     / _ \  
| |_) | |___| |___ / ___ \ 
|____/|_____|_____/_/   \_\

http://bela.io

C++ Real-Time Audio Programming with Bela - Lecture 14: ADSR
*/

// ADSR.h: header file for defining the ADSR class

#pragma once

#include "Ramp.h"

class ADSR {
private:
	// ADSR state machine variables, used internally
	enum State {
		StateOff = 0,
		StateAttack,
		StateDecay,
		StateSustain,
		StateRelease
	};

public:
	// Constructor
	ADSR();
	
	// Constructor with argument
	ADSR(float sampleRate);
	
	// Set the sample rate, used for all calculations
	void setSampleRate(float rate);
	
	// Start the envelope, going to the Attack state
	void trigger();
	
	// Stop the envelope, going to the Release state
	void release();
	
	// Calculate the next sample of output, changing the envelope
	// state as needed
	float process(); 
	
	// Indicate whether the envelope is active or not (i.e. in
	// anything other than the Off state
	bool isActive();
	
	// Methods for getting and setting parameters
	float getAttackTime() { return attackTime_; }
	float getDecayTime() { return decayTime_; }
	float getSustainLevel() { return sustainLevel_; }
	float getReleaseTime() { return releaseTime_; }
	
	void setAttackTime(float attackTime);
	void setDecayTime(float decayTime);	
	void setSustainLevel(float sustainLevel);
	void setReleaseTime(float releaseTime);
	
	// Destructor
	~ADSR();

private:
	// State variables and parameters, not accessible to the outside world
	float attackTime_;
	float decayTime_;
	float sustainLevel_;
	float releaseTime_;
	
	State state_;			// Current state of the ADSR (one of the enum values above)
	Ramp ramp_;				// Line segment generator
};