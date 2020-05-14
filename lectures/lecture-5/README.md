# Lecture 5: Classes and Objects

## [Watch Lecture 5 on YouTube](https://www.youtube.com/watch?v=wXuP8P8I-K0)

This lecture explains how to work with C++ classes and objects, while introducing the principles of additive synthesis. The lecture explains why simple digital square and sawtooth oscillators often sound so bad, and how additive synthesis can produce a better sounding oscillator.

## What you'll learn in this lecture

* Basics of C++ classes
* Working with arrays of objects
* Principles of additive synthesis

## What you'll make in this lecture

* An additive synthesis waveform generator

## Code examples

**wavetable-class**: implements a wavetable oscillator using a C++ class. Includes linear interpolation and GUI controls for frequency and amplitude.

**additive-synth**: a partially-complete example creating an additive synthesiser with controllable amplitudes for each harmonic. In the lecture you will fill in the code to process each oscillator.

## About this course

This course is co-developed by Bela (Augmented Instruments Ltd) and Queen Mary University of London. The materials are based on a Master's module "Music and Audio Programming", taught by [Dr Andrew McPherson](http://instrumentslab.org) in the [School of Electronic Engineering and Computer Science](http://www.eecs.qmul.ac.uk). The module is offered on degree programmes including:

* [MSc in Sound and Music Computing](https://www.qmul.ac.uk/postgraduate/taught/coursefinder/courses/129308.html), a one-year Master's programme
* [PhD in Artificial Intelligence and Music](http://www.aim.qmul.ac.uk), a 4-year PhD programme with fully-funded studentships for UK and international students

## Recommended parts

Running the examples in this course assumes that you have a [Bela Starter Kit](https://shop.bela.io/products/bela-starter-kit) or [Bela Mini Starter Kit](https://shop.bela.io/products/bela-mini-starter-kit).

This lecture does not require any other electronic hardware. However, other lectures will make use of sensors and other components. See [Lecture 0](../lecture-0) for a list of recommended parts.

## Additional references

### Classes in C++

* Online tutorial: [C++ Classes](https://www.cplusplus.com/doc/tutorial/classes/) at [cplusplus.com](https://cplusplus.com)
* YouTube video: [C++ Tutorial for Beginners](https://www.youtube.com/watch?v=vLnPwxZdW4Y) by freeCodeCamp.org

### The C++ `vector` class

* `vector` [reference documentation](https://www.cplusplus.com/reference/vector/vector/)

### Band-limited waveform synthesis

* Paper: T. Stilson and J. O. Smith, [Alias-Free Digital Synthesis of Classic Analog Waveforms](https://ccrma.stanford.edu/~stilti/papers/blit.pdf), International Computer Music Conference, 1996.
* Video: [The amazing usefulness of band limited impulse trains, shown for oscillator banks](https://www.youtube.com/watch?v=lpM4Tawq-XU), Stefan Stenzel, Audio Developer Conference 2017.
* Blog post: [Band-limiting techniques for digital oscillators (metafunction.co.uk)](http://metafunction.co.uk/all-about-digital-oscillators-part-2-blits-bleps/)
* Book: Beat Frei, [Digital Sound Generation](https://www.zhdk.ch/file/live/12/1253cbdc4679c70f0617b94877b80ffe9203764d/digital_sound_generation_1.pdf), Institute for Computer Music and Sound Technology (ICST), Zurich University of the Arts, 2019
