# Lecture 17: Block-based processing

## [Watch Lecture 17 on YouTube](https://www.youtube.com/watch?v=2uyWn8P0CVg)

This lecture is the second of a two-part series on MIDI, the industry standard protocol for communicating between musical devices such as keyboards and synths. It picks up where [Lecture 15](../lecture-15) left off, implementing pitch wheel, modulation wheel and control change messages in a basic MIDI synth. In the process it covers low-frequency oscillators (LFOs) for vibrato and portamento.

## What you'll learn in this lecture

* Generating and processing windows of a signal
* The Fast Fourier Transform (FFT)
* Sending data to the Bela GUI

## What you'll make in this lecture

* Two simple spectrum analysers with LEDs and GUI

## Code examples

**fft-led**: Simple project using the FFT to calculate high and low frequency content and blink LEDs. Also shows sending data to the Bela GUI.

**fft-circular-buffer**: Plot a real-time spectrum of the signal using the FFT. Your task is to implement the circular buffer code.

## About this course

This course is co-developed by Bela (Augmented Instruments Ltd) and Queen Mary University of London. The materials are based on a Master's module "Music and Audio Programming", taught by [Dr Andrew McPherson](http://instrumentslab.org) in the [School of Electronic Engineering and Computer Science](http://www.eecs.qmul.ac.uk). The module is offered on degree programmes including:

* [MSc in Sound and Music Computing](https://www.qmul.ac.uk/postgraduate/taught/coursefinder/courses/129308.html), a one-year Master's programme
* [PhD in Artificial Intelligence and Music](http://www.aim.qmul.ac.uk), a 4-year PhD programme with fully-funded studentships for UK and international students

## Recommended materials

Running the examples in this course assumes that you have a [Bela Starter Kit](https://shop.bela.io/products/bela-starter-kit) or [Bela Mini Starter Kit](https://shop.bela.io/products/bela-mini-starter-kit).

## Further reading

