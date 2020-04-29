/*
 ____  _____ _        _
| __ )| ____| |      / \
|  _ \|  _| | |     / _ \
| |_) | |___| |___ / ___ \
|____/|_____|_____/_/   \_\

The platform for ultra-low latency audio and sensor processing

http://bela.io

A project of the Augmented Instruments Laboratory within the
Centre for Digital Music at Queen Mary University of London.
http://www.eecs.qmul.ac.uk/~andrewm

(c) 2016 Augmented Instruments Laboratory: Andrew McPherson,
	Astrid Bin, Liam Donovan, Christian Heinrichs, Robert Jack,
	Giulio Moro, Laurel Pardue, Victor Zappi. All rights reserved.

The Bela software is distributed under the GNU Lesser General Public License
(LGPL 3.0), available here: https://www.gnu.org/licenses/lgpl-3.0.txt
*/

// Sine.cpp: file for implementing the sine oscillator class

#include <libraries/math_neon/math_neon.h>
#include "Sine.h"

// Default constructor: call the specific constructor with a default value
Sine::Sine() {}

// Constructor taking a sample rate
// Can also use initialisation lists instead of setting
// variables inside the function
Sine::Sine(float sampleRate) {
	setup(sampleRate);
}

// Set the sample rate
void Sine::setup(float rate) {
	frequency_ = 440.0;
	phase_ = 0;
	sampleRate_ = rate;
}

// Set the oscillator frequency
void Sine::setFrequency(float f) {
	frequency_ = f;
}

// Get the oscillator frequency
float Sine::getFrequency() {
	return frequency_;
}

// Get the next sample and update the phase
float Sine::nextSample() {
	// Increment and wrap the phase
	float out = sinf_neon(phase_);
	phase_ += 2.f * (float)M_PI * frequency_ / sampleRate_;
	while(phase_ >= (float)M_PI)
		phase_ -= 2.f * (float)M_PI;
	return out;
}

// Destructor
Sine::~Sine() {
	// Nothing to do here
}
