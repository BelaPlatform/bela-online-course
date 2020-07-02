# Lecture 13: State Machines

## [Watch Lecture 13 on YouTube](https://www.youtube.com/watch?v=x1mlHEUwl_8)

This lecture introduces the concept of the finite state machine (FSM or state machine for short). Many practical systems, audio-related and otherwise, can be modelled as state machines. This lecture presents applications to a metronome which marks the bar lines and various forms of sensor de-noising. It lays the groundwork for the ADSR envelope to be covered in a later lecture.

## What you'll learn in this lecture

* Structure and uses of state machines
* Debouncing buttons
* Hysteresis

## What you'll make in this lecture

* Metronome which marks the bar lines
* Button debouncer
* Comparator with hysteresis

## Code examples

**metronome-envelope**: Update to the metronome project from Lecture 9 which generates the tick sound using an exponential envelope instead of an audio file. In the lecture, this is extended to have a different pitch for the first beat of the bar.

**scope-button**: Simple example which displays the value of a digital input on the Bela oscilloscope.

**debounce**: Template project for implementing a state machine to debounce a push button.

**hysteresis-comparator**: Implements a simple comparator, with the task in the lecture to add hysteresis (variable threshold) for noise immunity.

## About this course

This course is co-developed by Bela (Augmented Instruments Ltd) and Queen Mary University of London. The materials are based on a Master's module "Music and Audio Programming", taught by [Dr Andrew McPherson](http://instrumentslab.org) in the [School of Electronic Engineering and Computer Science](http://www.eecs.qmul.ac.uk). The module is offered on degree programmes including:

* [MSc in Sound and Music Computing](https://www.qmul.ac.uk/postgraduate/taught/coursefinder/courses/129308.html), a one-year Master's programme
* [PhD in Artificial Intelligence and Music](http://www.aim.qmul.ac.uk), a 4-year PhD programme with fully-funded studentships for UK and international students

## Recommended parts

Running the examples in this course assumes that you have a [Bela Starter Kit](https://shop.bela.io/products/bela-starter-kit) or [Bela Mini Starter Kit](https://shop.bela.io/products/bela-mini-starter-kit).

* Solderless breadboard ([Rapid](https://www.rapidonline.com/rapid-tp-039-solderless-breadboard-transparent-400-points-34-0671) | [Adafruit](https://www.adafruit.com/product/64))
* 1x pushbutton ([Rapid](https://www.rapidonline.com/omron-tactile-pcb-switch-b3f-4000-12x12-flat-type--78-0286) | [Adafruit](https://www.adafruit.com/product/1119))
* 1x force-sensing resistor ([Rapid](https://www.rapidonline.com/taiwan-alpha-43mm-square-membrane-force-sensor-78-4008) | [Adafruit](https://www.adafruit.com/product/1075))
* 1x LED (any colour) ([Rapid](https://www.rapidonline.com/kingbright-l-7113gd-5mm-2-2v-green-led-20mcd-55-0120) | [Adafruit](https://www.adafruit.com/product/298))
* 1x 10k resistor ([Rapid](https://www.rapidonline.com/truohm-cr-025-10k-carbon-film-resistor-0-25w-pack-of-100-62-0394) | [Adafruit](https://www.adafruit.com/product/2784))
* 1x 220 ohm resistor ([Rapid](https://www.rapidonline.com/truohm-cr-025-220r-carbon-film-resistor-0-25w-pack-of-100-62-0354) | [Adafruit](https://www.adafruit.com/product/2780))
* Jumper wires ([Rapid](https://www.rapidonline.com/rapid-jw-003-breadboard-jumper-wires-bundle-of-75-34-0673) | [Adafruit](https://www.adafruit.com/product/153))
