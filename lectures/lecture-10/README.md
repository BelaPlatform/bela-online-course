# Lecture 10: Latency

## [Watch Lecture 10 on YouTube](https://www.youtube.com/watch?v=sy3TIISpnYU)

This lecture provides a comprehensive introduction to latency: what it is, where it comes from, and what you can do about it. It includes two approaches to measuring latency, the first using a bench-top oscilloscope and function generator, and the second an automatic latency tester running on Bela.

## What you'll learn in this lecture

* What latency is, and why it matters
* Sources of latency
* How to measure latency

## What you'll make in this lecture

* An automatic latency tester

## Code examples

**latency-tester**: Project which sends a regular pulse to the audio output and measures how long it takes to return, providing an estimate of the latency of Bela and any external audio device.

## About this course

This course is co-developed by Bela (Augmented Instruments Ltd) and Queen Mary University of London. The materials are based on a Master's module "Music and Audio Programming", taught by [Dr Andrew McPherson](http://instrumentslab.org) in the [School of Electronic Engineering and Computer Science](http://www.eecs.qmul.ac.uk). The module is offered on degree programmes including:

* [MSc in Sound and Music Computing](https://www.qmul.ac.uk/postgraduate/taught/coursefinder/courses/129308.html), a one-year Master's programme
* [PhD in Artificial Intelligence and Music](http://www.aim.qmul.ac.uk), a 4-year PhD programme with fully-funded studentships for UK and international students

## Recommended parts

Running the examples in this course assumes that you have a [Bela Starter Kit](https://shop.bela.io/products/bela-starter-kit) or [Bela Mini Starter Kit](https://shop.bela.io/products/bela-mini-starter-kit). Note that the analog outputs are only available on the original Bela board, and not on Bela Mini.

This lecture also presents a demo with an oscilloscope and a function generator. You don't need to have these to follow along with the example, but if you do, you can repeat the test for yourself.

To use the automatic latency tester project, you will need a loopback cable: either a 3.5mm stereo audio cable or socket wires to connect between Bela's audio input and audio output.

## Further reading

Here are further papers on latency in digital audio and interactive systems:

* A. McPherson, R. Jack and G. Moro. [Action-sound latency: are our tools fast enough?]((http://www.eecs.qmul.ac.uk/~andrewm/mcpherson_nime2016.pdf)) Proceedings of the International Conference on New Interfaces for Musical Expression, 2016.
* R. Jack, T. Stockman and A. McPherson. [Action-sound Latency and the Perceived Quality of Digital Musical Instruments: Comparing Professional Percussionists and Amateur Musicians](https://www.researchgate.net/profile/Robert_Jack4/publication/326464649_Action-sound_Latency_and_the_Perceived_Quality_of_Digital_Musical_Instruments_Comparing_Professional_Percussionists_and_Amateur_Musicians/links/5b4f5fcdaca27217ffa1e7fb/Action-sound-Latency-and-the-Perceived-Quality-of-Digital-Musical-Instruments-Comparing-Professional-Percussionists-and-Amateur-Musicians.pdf). *Music Perception*. Vol. 36, Issue 1, 2018. 
* D. Wessel and M. Wright. [Problems and prospects for intimate musical control of computers](http://opensoundcontrol.org/files/p1-wessel-1.pdf). *Computer Music Journal*, Vol. 26, Issue 3, 2002.