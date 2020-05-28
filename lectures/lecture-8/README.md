# Lecture 8: Filters

## [Watch Lecture 8 on YouTube](https://www.youtube.com/watch?v=XVOdqJy-Rfg)

This lecture explains how to implement digital filters in C++. It introduces the terminology behind digital filters and shows how to take a filter equation and turn it into real-time code. By the end of the lecture, you will create several example filters including an adjustable resonant lowpass filter.

This lecture does not cover the mathematics of filter design; more resources on this topic are linked below.

## What you'll learn in this lecture

* Basic theory of digital filters
* Filter terminology: cutoff, bandwidth, Q, order
* Turning filter equations into code

## What you'll make in this lecture

* An adjustable resonant lowpass filter

## Code examples

**sample-player-filter**: Template for implementing digital filters. Plays an audio sample in a loop, with space in `render()` to implement your own filters.

**resonant-lowpass**: Provides the infrastructure for calculating coefficients of a resonant lowpass filter. In lecture, the filter equation will be implemented and controls will be added to adjust the cutoff frequency and Q.

## About this course

This course is co-developed by Bela (Augmented Instruments Ltd) and Queen Mary University of London. The materials are based on a Master's module "Music and Audio Programming", taught by [Dr Andrew McPherson](http://instrumentslab.org) in the [School of Electronic Engineering and Computer Science](http://www.eecs.qmul.ac.uk). The module is offered on degree programmes including:

* [MSc in Sound and Music Computing](https://www.qmul.ac.uk/postgraduate/taught/coursefinder/courses/129308.html), a one-year Master's programme
* [PhD in Artificial Intelligence and Music](http://www.aim.qmul.ac.uk), a 4-year PhD programme with fully-funded studentships for UK and international students

## Recommended parts

Running the examples in this course assumes that you have a [Bela Starter Kit](https://shop.bela.io/products/bela-starter-kit) or [Bela Mini Starter Kit](https://shop.bela.io/products/bela-mini-starter-kit). Note that the analog outputs are only available on the original Bela board, and not on Bela Mini.

The last step of this lecture optionally uses potentiometers to adjust filter parameters. This requires the following components:

* Solderless breadboard ([Rapid](https://www.rapidonline.com/rapid-tp-039-solderless-breadboard-transparent-400-points-34-0671) | [Adafruit](https://www.adafruit.com/product/64))
* 3x 10k potentiometers ([Rapid](https://www.rapidonline.com/taiwan-alpha-rv16af-10k-lin-16mm-metal-case-pcb-potentiometer-65-0715) | [Adafruit](https://www.adafruit.com/product/4133))
* Jumper wires ([Rapid](https://www.rapidonline.com/rapid-jw-003-breadboard-jumper-wires-bundle-of-75-34-0673) | [Adafruit](https://www.adafruit.com/product/153))

## Additional references

* Alan V. Oppenheim and Ronald W. Shafer, *Discrete-Time Signal Processing*, 3rd edition. [Publisher link](http://www.pearsonhighered.com/product?ISBN=0131988425). See also the same class on [MIT OpenCourseware](https://ocw.mit.edu/courses/electrical-engineering-and-computer-science/6-341-discrete-time-signal-processing-fall-2005/).
* Julius O. Smith, [Mathematics of the Discrete Fourier Transform (DFT)](https://ccrma.stanford.edu/~jos/mdft/) (free online textbook).
* Julius O. Smith, [Introduction to Digital Filters](https://ccrma.stanford.edu/~jos/filters/) (free online textbook).
* Joshua D. Reiss and Andrew McPherson, *Audio Effects: Theory, Implementation and Application*. [Publisher link](https://www.taylorfrancis.com/books/9780429097232).
* David Doran, [An explanation of the Z-transform](https://www.youtube.com/watch?v=B4IyRw1zvvA) (YouTube video).