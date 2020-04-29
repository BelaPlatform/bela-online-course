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
#pragma once
// Sine.h: header file for sine oscillator class

class Sine {
public:
	Sine(); // Default constructor
	Sine(float sampleRate); // Constructor with argument

	void setup(float rate); // Set the sample rate
	void setFrequency(float f); // Set the oscillator frequency
	float getFrequency(); // Get the oscillator frequency

	float nextSample(); // Get the next sample and update the phase

	~Sine(); // Destructor

private:
	float sampleRate_; // Sample rate of the audio
	float frequency_; // Frequency of the oscillator
	float phase_; // Phase of the oscillator
};
