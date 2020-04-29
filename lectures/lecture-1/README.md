# Lecture 1: Real time

## [Watch Lecture 1 on YouTube](https://www.youtube.com/watch?v=N3XkQqhE6sY)

This lecture explains the concepts behind real-time audio and shows you how to program an oscillator that runs in real time.

## What you'll learn in this lecture

* Principles of real-time audio
* How to write real-time C++ code

## What you'll make in this lecture

* Sine-wave oscillator

## Code example

**sine-generator**: a sine wave oscillator that does *not* run in real time: it generates 5 seconds of audio at the beginning then plays it back. Used as a starting point for code exercises.

**sine-generator-rt**: an incomplete example which over the course of the lecture will be turned into a real-time sine wave oscillator.

## About this course

This course is co-developed by Bela (Augmented Instruments Ltd) and Queen Mary University of London. The materials are based on a Master's module "Music and Audio Programming", taught by [Dr Andrew McPherson](http://instrumentslab.org) in the [School of Electronic Engineering and Computer Science](http://www.eecs.qmul.ac.uk). The module is offered on degree programmes including:

* [MSc in Sound and Music Computing](https://www.qmul.ac.uk/postgraduate/taught/coursefinder/courses/129308.html), a one-year Master's programme
* [PhD in Artificial Intelligence and Music](http://www.aim.qmul.ac.uk), a 4-year PhD programme with fully-funded studentships for UK and international students

## Recommended parts

Running the examples in this course assumes that you have a [Bela Starter Kit](https://shop.bela.io/products/bela-starter-kit) or [Bela Mini Starter Kit](https://shop.bela.io/products/bela-mini-starter-kit).

This lecture does not require any other electronic hardware. However, other lectures will make use of sensors and other components. See [Lecture 0](../lecture-0) for a list of recommended parts.

## Further reading

This lecture references a few basic terms related to discrete-time signal processing. An excellent reference on discrete-time signal processing is the following textbook:

* Alan V. Oppenheim and Ronald W. Shafer, *Discrete-Time Signal Processing*, 3rd edition. [Publisher link](http://www.pearsonhighered.com/product?ISBN=0131988425). See also the same class on [MIT OpenCourseware](https://ocw.mit.edu/courses/electrical-engineering-and-computer-science/6-341-discrete-time-signal-processing-fall-2005/).