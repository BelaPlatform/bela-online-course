# Lecture 14: ADSR

## [Watch Lecture 14 on YouTube](https://youtu.be/Ti_1H3TdkZY)

This lecture introduces the ADSR (attack-decay-sustain-release) envelope, which is commonly found in modular synthesis because of the way it simulates the profile of traditional musical instruments. The lecture covers how to implement an ADSR as a state machine using either linear or exponential segments.

## What you'll learn in this lecture

* The ADSR (attack-decay-sustain-release) envelope
* Implementation using state machines and line segments
* Class-based implementations

## What you'll make in this lecture

* ADSR envelope generator controlled by a button
* ADSR with linear or exponential segments

## Code examples

**adsr**: Template for implementing the ADSR based on the `Ramp` class covered Lecture 12, which generates individua line segments.

**adsr-class**: Container code for implementing the ADSR in its own self-contained class. The class definition is given in `ADSR.h` and your task is to fill in the code in `ADSR.cpp`. After that, two ADSR objects can be used in `render.cpp` to control amplitude and filter.

## About this course

This course is co-developed by Bela (Augmented Instruments Ltd) and Queen Mary University of London. The materials are based on a Master's module "Music and Audio Programming", taught by [Dr Andrew McPherson](http://instrumentslab.org) in the [School of Electronic Engineering and Computer Science](http://www.eecs.qmul.ac.uk). The module is offered on degree programmes including:

* [MSc in Sound and Music Computing](https://www.qmul.ac.uk/postgraduate/taught/coursefinder/courses/129308.html), a one-year Master's programme
* [PhD in Artificial Intelligence and Music](http://www.aim.qmul.ac.uk), a 4-year PhD programme with fully-funded studentships for UK and international students

## Recommended parts

Running the examples in this course assumes that you have a [Bela Starter Kit](https://shop.bela.io/products/bela-starter-kit) or [Bela Mini Starter Kit](https://shop.bela.io/products/bela-mini-starter-kit).

* Solderless breadboard ([Rapid](https://www.rapidonline.com/rapid-tp-039-solderless-breadboard-transparent-400-points-34-0671) | [Adafruit](https://www.adafruit.com/product/64))
* 1x pushbutton ([Rapid](https://www.rapidonline.com/omron-tactile-pcb-switch-b3f-4000-12x12-flat-type--78-0286) | [Adafruit](https://www.adafruit.com/product/1119))
* 1x 10k resistor ([Rapid](https://www.rapidonline.com/truohm-cr-025-10k-carbon-film-resistor-0-25w-pack-of-100-62-0394) | [Adafruit](https://www.adafruit.com/product/2784))
* Jumper wires ([Rapid](https://www.rapidonline.com/rapid-jw-003-breadboard-jumper-wires-bundle-of-75-34-0673) | [Adafruit](https://www.adafruit.com/product/153))
