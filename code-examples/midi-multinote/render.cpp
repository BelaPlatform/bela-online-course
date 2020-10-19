/*
 ____  _____ _        _    
| __ )| ____| |      / \   
|  _ \|  _| | |     / _ \  
| |_) | |___| |___ / ___ \ 
|____/|_____|_____/_/   \_\

http://bela.io

C++ Real-Time Audio Programming with Bela - Lecture 15: MIDI part 1
midi-multinote: sine wave MIDI synth which keeps track of multiple key presses
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

// List of active notes
const int kMaxNotes = 16;
int gActiveNotes[kMaxNotes];
int gActiveNoteCount = 0;

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

// Called when a MIDI note on is received
// Takes two arguments: note number and velocity
void noteOn(int noteNumber, int velocity)
{
	// Add this note to the list of active notes
	if(gActiveNoteCount < kMaxNotes) {
		gActiveNotes[gActiveNoteCount] = noteNumber;
		gActiveNoteCount++;

		// Map note number to frequency
		gFrequency = powf(2.0, (noteNumber - 69)/12.0) * 440.0;
		
		// Map velocity to amplitude on a decibel scale
		float decibels = map(velocity, 1, 127, -40, 0);
		gAmplitude = powf(10.0, decibels / 20.0);
		
		rt_printf("Note on: Frequency: %f, Amplitude: %f\n", gFrequency, gAmplitude);
	}
}

// Called when a MIDI note off is received
void noteOff(int noteNumber)
{
	// When we receive a note off, it might be the most recent note
	// that we played, or it might be an earlier note. We need to figure
	// out which indexes correspond to this note number.
	
	bool activeNoteChanged = false;
	
	// Go through all the active notes and remove any with this number
	for(int i = gActiveNoteCount - 1; i >= 0; i--) {
		if(gActiveNotes[i] == noteNumber) {
			// Found a match: is it the most recent note?
			
			// TODO 1: if the note is the most recent, set the flag
			// that says we will change the active note (activeNoteChanged)
			// But how do we know if this note in the array is the most
			// recent one? (hint: it depends on the value of i)
			
			
			// TODO 2: move all the later notes to be one slot earlier in the
			// array. Hint: you will need another for() loop with a new
			// index, starting from "i" and counting upward
	
			// TODO 3: decrease the number of active notes
		}
	}

	rt_printf("Note off: %d notes remaining\n", gActiveNoteCount);
	
	if(gActiveNoteCount == 0) {
		// No notes left
		gAmplitude = 0;
	}
	else if(activeNoteChanged) {
		// Update the frequency but don't retrigger
		int mostRecentNote = gActiveNotes[gActiveNoteCount - 1];
		
		gFrequency = powf(2.0, (mostRecentNote - 69)/12.0) * 440.0;
		
		rt_printf("Note changed: new frequency %f\n", gFrequency);
	}
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
		if(gActiveNoteCount > 0) {
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

