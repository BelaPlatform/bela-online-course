# Lecture 12: Envelopes

## [Watch Lecture 12 on YouTube](https://www.youtube.com/watch?v=xDdul0FhAAY)

This lecture explains envelopes: what they are, how to synthesise them and how to measure the envelopes of existing audio signals. It covers linear envelopes (ramps) and exponential envelopes. ADSR (attack-decay-sustain-release) envelopes will be covered in a later lecture.

## What you'll learn in this lecture

* Linear and exponential envelopes
* Generating ramps by counting samples
* Finding the envelope of an audio signal

## What you'll make in this lecture

* A ramp-controlled filter (several versions)
* A simple percussion instrument
* An envelope follower auto-wah effect

## Code examples

**ramp-filter**: Template project providing a wavetable oscillator and filter. The task is to generate a linear envelope to change the cutoff frequency of the filter. Later in the lecture, analog controls are added.

**ramp-filter-class**: The same idea as `ramp-filter` but with the envelope moved into a class. The task is to implement `Ramp.cpp`.

**percussion**: A simple percussion instrument to be completed with an exponential envelope and a pushbutton attached to a digital instrument.

**envelope-follower**: Template for creating an auto-wah effect where the cutoff frequency of a resonant filter tracks the envelope of the incoming audio signal.

## About this course

This course is co-developed by Bela (Augmented Instruments Ltd) and Queen Mary University of London. The materials are based on a Master's module "Music and Audio Programming", taught by [Dr Andrew McPherson](http://instrumentslab.org) in the [School of Electronic Engineering and Computer Science](http://www.eecs.qmul.ac.uk). The module is offered on degree programmes including:

* [MSc in Sound and Music Computing](https://www.qmul.ac.uk/postgraduate/taught/coursefinder/courses/129308.html), a one-year Master's programme
* [PhD in Artificial Intelligence and Music](http://www.aim.qmul.ac.uk), a 4-year PhD programme with fully-funded studentships for UK and international students

## Recommended parts

Running the examples in this course assumes that you have a [Bela Starter Kit](https://shop.bela.io/products/bela-starter-kit) or [Bela Mini Starter Kit](https://shop.bela.io/products/bela-mini-starter-kit). Note that the analog outputs are only available on the original Bela board, and not on Bela Mini.

This lecture also uses several electronic components:

* Solderless breadboard ([Rapid](https://www.rapidonline.com/rapid-tp-039-solderless-breadboard-transparent-400-points-34-0671) | [Adafruit](https://www.adafruit.com/product/64))
* 1x pushbutton ([Rapid](https://www.rapidonline.com/omron-tactile-pcb-switch-b3f-4000-12x12-flat-type--78-0286) | [Adafruit](https://www.adafruit.com/product/1119))
* 3x 10k potentiometers ([Rapid](https://www.rapidonline.com/taiwan-alpha-rv16af-10k-lin-16mm-metal-case-pcb-potentiometer-65-0715) | [Adafruit](https://www.adafruit.com/product/4133))
* 1x LED (any colour) ([Rapid](https://www.rapidonline.com/kingbright-l-7113gd-5mm-2-2v-green-led-20mcd-55-0120) | [Adafruit](https://www.adafruit.com/product/298))
* 1x 10k resistor ([Rapid](https://www.rapidonline.com/truohm-cr-025-10k-carbon-film-resistor-0-25w-pack-of-100-62-0394) | [Adafruit](https://www.adafruit.com/product/2784))
* 1x 220 ohm resistor ([Rapid](https://www.rapidonline.com/truohm-cr-025-220r-carbon-film-resistor-0-25w-pack-of-100-62-0354) | [Adafruit](https://www.adafruit.com/product/2780))
* Jumper wires ([Rapid](https://www.rapidonline.com/rapid-jw-003-breadboard-jumper-wires-bundle-of-75-34-0673) | [Adafruit](https://www.adafruit.com/product/153))

## Further reading

More information on calculating envelopes can be found in Chapter X of this textbook:

* Joshua D. Reiss and Andrew McPherson, *Audio Effects: Theory, Implementation and Application*. [Publisher link](https://www.taylorfrancis.com/books/9780429097232).