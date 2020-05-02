# Lecture 2: Playing recorded samples

## [Watch Lecture 2 on YouTube](https://www.youtube.com/watch?v=adZhmox310Q)

This lecture explains how to load recorded audio samples and play them in real time.

## What you'll learn in this lecture

* The Bela C++ API
* Working with buffers (arrays) in C++

## What you'll make in this lecture

* Sample (audio file) player

## Code examples

**sample-player**: a partially complete project that plays a sound loaded from the flash storage. The sample loading is handled for you, but you have to fill in the real-time playback code in `render()`.

**sample-player-stereo**: a variation on `sample-player` that plays multi-channel audio files. Like the previous example, it is incomplete and you need to fill in the critical sections in `render()`.

## About this course

This course is co-developed by Bela (Augmented Instruments Ltd) and Queen Mary University of London. The materials are based on a Master's module "Music and Audio Programming", taught by [Dr Andrew McPherson](http://instrumentslab.org) in the [School of Electronic Engineering and Computer Science](http://www.eecs.qmul.ac.uk). The module is offered on degree programmes including:

* [MSc in Sound and Music Computing](https://www.qmul.ac.uk/postgraduate/taught/coursefinder/courses/129308.html), a one-year Master's programme
* [PhD in Artificial Intelligence and Music](http://www.aim.qmul.ac.uk), a 4-year PhD programme with fully-funded studentships for UK and international students

## Recommended parts

Running the examples in this course assumes that you have a [Bela Starter Kit](https://shop.bela.io/products/bela-starter-kit) or [Bela Mini Starter Kit](https://shop.bela.io/products/bela-mini-starter-kit).

This lecture does not require any other electronic hardware. However, other lectures will make use of sensors and other components. See [Lecture 0](../lecture-0) for a list of recommended parts.