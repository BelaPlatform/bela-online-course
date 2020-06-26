# Lecture 11: Circular Buffers

## [Watch Lecture 11 on YouTube](https://www.youtube.com/watch?v=xQBftd7WNY8)

This lecture introduces circular buffers as a way to save the previous history of an audio signal. Circular buffers can be used to create delays and delay-based audio effects such as echo, chorus and flanger effects. Over the course of the lecture, we progressively build up a circular buffer example with adjustable delay and feedback.

## What you'll learn in this lecture

* Keeping track of previous audio samples
* Why and how to use circular buffers
* Creating an audio delay

## What you'll make in this lecture

* An adjustable delay and an echo effect

## Code examples

**circular-buffer**: Template project which is built up in several steps over the lecture. Plays a sound file in a loop. During the lecture we implement a circular buffer with read and write pointers and adjustable delay.

## About this course

This course is co-developed by Bela (Augmented Instruments Ltd) and Queen Mary University of London. The materials are based on a Master's module "Music and Audio Programming", taught by [Dr Andrew McPherson](http://instrumentslab.org) in the [School of Electronic Engineering and Computer Science](http://www.eecs.qmul.ac.uk). The module is offered on degree programmes including:

* [MSc in Sound and Music Computing](https://www.qmul.ac.uk/postgraduate/taught/coursefinder/courses/129308.html), a one-year Master's programme
* [PhD in Artificial Intelligence and Music](http://www.aim.qmul.ac.uk), a 4-year PhD programme with fully-funded studentships for UK and international students

## Recommended parts

Running the examples in this course assumes that you have a [Bela Starter Kit](https://shop.bela.io/products/bela-starter-kit) or [Bela Mini Starter Kit](https://shop.bela.io/products/bela-mini-starter-kit).

## Further reading

More information on delay-based audio effects, including vibrato, chorus, flanger and echo, can be found in Chapter 2 of this textbook:

* Joshua D. Reiss and Andrew McPherson, *Audio Effects: Theory, Implementation and Application*. [Publisher link](https://www.taylorfrancis.com/books/9780429097232).