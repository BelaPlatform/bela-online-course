# Lecture 18: Phase vocoder, part 1

## [Watch Lecture 18 on YouTube](https://www.youtube.com/watch?v=xGmRaTaBNZA)


This lecture continues a series on block-based processing, and is the first of two lectures on the phase vocoder, a powerful tool for manipulating audio in the frequency domain. This lecture covers the overlap-add technique, a common approach to dividing a signal into blocks, manipulating it in the frequency domain, then reconstructing it.

This lecture also introduces multi-threaded audio processing, showing how to move time-consuming calculations into a lower priority real-time thread.

## What you'll learn in this lecture

* Segmenting a real-time signal into windows
* Working with overlapping windows (overlap-add)
* Multi-threaded audio processing

## What you'll make in this lecture

* A phase vocoder framework with simple effects

## Code examples

**fft-overlap-add**: This code provides a template for implementing the overlap-add block-based processing technique, with an optional simple example of a robotisation effect. 

**fft-overlap-add-threads**: This example extends `fft-overlap-add` to move the FFT calculation to a lower-priority thread to allow glitch-free execution with small real-time audio buffer sizes.

## About this course

This course is co-developed by Bela (Augmented Instruments Ltd) and Queen Mary University of London. The materials are based on a Master's module "Music and Audio Programming", taught by [Dr Andrew McPherson](http://instrumentslab.org) in the [School of Electronic Engineering and Computer Science](http://www.eecs.qmul.ac.uk). The module is offered on degree programmes including:

* [MSc in Sound and Music Computing](https://www.qmul.ac.uk/postgraduate/taught/coursefinder/courses/129308.html), a one-year Master's programme
* [PhD in Artificial Intelligence and Music](http://www.aim.qmul.ac.uk), a 4-year PhD programme with fully-funded studentships for UK and international students

## Recommended materials

Running the examples in this course assumes that you have a [Bela Starter Kit](https://shop.bela.io/products/bela-starter-kit) or [Bela Mini Starter Kit](https://shop.bela.io/products/bela-mini-starter-kit).

No external components are required for this lecture.

## Additional references

Here are some textbooks and other resources related to the Fast Fourier Transform and spectral audio processing:

* Alan V. Oppenheim and Ronald W. Shafer, *Discrete-Time Signal Processing*, 3rd edition. [Publisher link](http://www.pearsonhighered.com/product?ISBN=0131988425). See also the same class on [MIT OpenCourseware](https://ocw.mit.edu/courses/electrical-engineering-and-computer-science/6-341-discrete-time-signal-processing-fall-2005/).
* Julius O. Smith, [Mathematics of the Discrete Fourier Transform (DFT)](https://ccrma.stanford.edu/~jos/mdft/) (free online textbook).
* Julius O. Smith, [Spectral Audio Signal Processing](https://ccrma.stanford.edu/~jos/sasp/) (free online textbook).
* Joshua D. Reiss and Andrew McPherson, *Audio Effects: Theory, Implementation and Application*. [Publisher link](https://www.taylorfrancis.com/books/9780429097232).
* Richard Boulanger and Victor Lazzarini, editors, *The Audio Programming Book*. [Publisher link](https://mitpress.mit.edu/books/audio-programming-book)
* [A visual introduction to the Fourier transform](https://www.youtube.com/watch?v=spUNpyF58BY) on YouTube from 3Blue1Brown
* [Divide and Conquer: the FFT algorithm](https://www.youtube.com/watch?v=iTMn0Kt18tg) on YouTube from MIT OpenCourseWare (a mathematical explainer)
