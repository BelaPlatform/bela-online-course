/*
 ____  _____ _        _    
| __ )| ____| |      / \   
|  _ \|  _| | |     / _ \  
| |_) | |___| |___ / ___ \ 
|____/|_____|_____/_/   \_\

http://bela.io

C++ Real-Time Audio Programming with Bela - Lecture 15: MIDI part 1
midi-sinetone: basic sine wave synth controlled by MIDI
*/


// This project is based on the Bela example Communication/MIDI
// See the example for several more ways of working with MIDI on Bela.

#include <Bela.h>
#include <libraries/Midi/Midi.h>
#include <stdlib.h>
#include <cmath>

// Device for handling MIDI messages
Midi gMidi;

// Name of the MIDI port to use. Run 'amidi -l' on the console to see a list.
// Typical values: 
//   "hw:0,0,0" for a virtual device (from the computer)
//   "hw:1,0,0" for a USB device plugged into the Bela board
const char* gMidiPort0 = "hw:1,0,0";

// Oscillator state
float gPhase = 0;
float gFrequency = 0;
float gAmplitude = 0;
bool gIsNoteOn = 0;


bool setup(BelaContext *context, void *userData)
{
	// Initialise the MIDI device
	if(gMidi.readFrom(gMidiPort0) < 0) {
		rt_printf("Unable to read from MIDI port %s\n", gMidiPort0);
		return false;
	}
	gMidi.writeTo(gMidiPort0);
	gMidi.enableParser(true);

	return true;
}

void noteOn(int noteNumber, int velocity)
{
	// TODO: map MIDI note number to frequency
	gFrequency = 440;		// TODO!
	
	// TODO: map velocity to amplitude on a decibel scale
	// Hint: use a two-step process to first calculate the value in dB and
	//       then calculate gAmpliude from that
	gAmplitude = 0.5;
	
	// Indicate the note is on (so the oscillator runs)
	gIsNoteOn = true;	
}

void noteOff(int noteNumber)
{
	// TODO: turn the note off
}

void render(BelaContext *context, void *userData)
{
	// At the beginning of each callback, look for available MIDI
	// messages that have come in since the last block
	while(gMidi.getParser()->numAvailableMessages() > 0) {
		MidiChannelMessage message;
		message = gMidi.getParser()->getNextChannelMessage();
		message.prettyPrint();		// Print the message data
		
		// A MIDI "note on" message type might actually hold a real
		// note onset (e.g. key press), or it might hold a note off (key release).
		// The latter is signified by a velocity of 0.
		if(message.getType() == kmmNoteOn) {
			int noteNumber = message.getDataByte(0);
			int velocity = message.getDataByte(1);
			
			// Velocity of 0 is really a note off
			if(velocity == 0) {
				noteOff(noteNumber);
			}
			else {
				noteOn(noteNumber, velocity);
			}
			
			rt_printf("Frequency: %f, Amplitude: %f\n", gFrequency, gAmplitude);
		}
		else if(message.getType() == kmmNoteOff) {
			// We can also encounter the "note off" message type which is the same
			// as "note on" with a velocity of 0.
			int noteNumber = message.getDataByte(0);
			
			noteOff(noteNumber);
		}
	}

	// Now calculate the audio for this block
	for(unsigned int n = 0; n < context->audioFrames; n++) {
		float value = 0;
		
		// Run the oscillator whenever a note is on
		if(gIsNoteOn) {
			gPhase += 2.0 * M_PI * gFrequency / context->audioSampleRate;
			if(gPhase > M_PI)
				gPhase -= 2.0 * M_PI;
			value = sin(gPhase) * gAmplitude;
		} 
		
		for(unsigned int ch = 0; ch < context->audioOutChannels; ++ch)
			audioWrite(context, n, ch, value);
	}
}

void cleanup(BelaContext *context, void *userData)
{

}

