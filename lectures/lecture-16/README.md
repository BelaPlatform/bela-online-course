# Lecture 16: MIDI, part 2

## [Watch Lecture 16 on YouTube](https://www.youtube.com/watch?v=no-iO3mAnr8)

This lecture is the second of a two-part series on MIDI, the industry standard protocol for communicating between musical devices such as keyboards and synths. It picks up where [Lecture 15](../lecture-15) left off, implementing pitch wheel, modulation wheel and control change messages in a basic MIDI synth. In the process it covers low-frequency oscillators (LFOs) for vibrato and portamento.

## What you'll learn in this lecture

* Handling MIDI pitch wheel messages
* Handling MIDI control change messages
* Low-frequency oscillators (LFOs)
* Portamento

## What you'll make in this lecture

* Monophonic MIDI synth with detuning and continuous pitch control

## Code examples

**midi-pitchwheel**: This project forms the basis of four coding exercises in the lecture, progressively adding features to the MIDI synth completed in [Lecture 15](../lecture-15).

## About this course

This course is co-developed by Bela (Augmented Instruments Ltd) and Queen Mary University of London. The materials are based on a Master's module "Music and Audio Programming", taught by [Dr Andrew McPherson](http://instrumentslab.org) in the [School of Electronic Engineering and Computer Science](http://www.eecs.qmul.ac.uk). The module is offered on degree programmes including:

* [MSc in Sound and Music Computing](https://www.qmul.ac.uk/postgraduate/taught/coursefinder/courses/129308.html), a one-year Master's programme
* [PhD in Artificial Intelligence and Music](http://www.aim.qmul.ac.uk), a 4-year PhD programme with fully-funded studentships for UK and international students

## Recommended materials

Running the examples in this course assumes that you have a [Bela Starter Kit](https://shop.bela.io/products/bela-starter-kit) or [Bela Mini Starter Kit](https://shop.bela.io/products/bela-mini-starter-kit).

This lecture requires a source of MIDI input, either a keyboard attached to the USB port of Bela or virtual keyboard software which can send MIDI messages to Bela from the host computer. The following software MIDI generators will work:

* [MidiKeys](https://flit.github.io/projects/midikeys/) for MacOS X
* [vmpk](https://vmpk.sourceforge.io), a cross-platform MIDI generator

## Further reading

* [Summary of MIDI messages](https://www.midi.org/specifications-old/item/table-1-summary-of-midi-message) from midi.org
* [MIDI controller numbers](https://www.midi.org/specifications-old/item/table-3-control-change-messages-data-bytes-2) from midi.org
* [General MIDI sound sets](https://www.midi.org/specifications-old/item/gm-level-1-sound-set) (i.e. Program Change message meaning) from midi.org
* [MIDI Polyphonic Expression (MPE) specification](https://www.midi.org/midi-articles/midi-polyphonic-expression-mpe) from midi.org
* [Hexadecimal tutorial](https://learn.sparkfun.com/tutorials/hexadecimal/all) from SparkFun
* [Changing pitch wheel range with RPN messages](http://midi.teragonaudio.com/tech/midispec/rpn.htm)