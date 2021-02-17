# Lecture 20: Phase vocoder, part 3

## [Watch Lecture 20 on YouTube](https://www.youtube.com/watch?v=2p_-jbl6Dyc)


This is the final lecture of a three-part series on the phase vocoder, a powerful tool for manipulating audio in the frequency domain. Where Lecture 19 explained how to estimate frequency components from the phase of FFT bins, this lecture now explains how to manipulate and resynthesise those components, producing a pitch shifter and other effects.

## What you'll learn in this lecture

* Modifying signals in the frequency domain
* Converting frequency to phase
* Analysis and synthesis windows

## What you'll make in this lecture

* Pitch shifting, robotisation and whisperisation effects

## Code examples

**fft-robotisation**: Zeroes the phase of each FFT bin at each hop to produce regularly spaced frequencies, leading to a robot-like effect when applied to a voice. You will modify the code to add analysis and synthesis windows, then make a version which produces a whisperisation effect instead.

**fft-pitch-shifter**: The capstone project of the phase vocoder lecture series. Convert from phase to frequency and back again, scaling the frequencies in the middle to shift the pitch of the sound without changing its timing.

**fft-robotisation-v2**: A different and more flexible approach to the robotisation effect, based on the principles used in the pitch shifter. You will implement code for rounding each frequency to the nearest multiple of a desired fundamental.

## About this course

This course is co-developed by Bela (Augmented Instruments Ltd) and Queen Mary University of London. The materials are based on a Master's module "Music and Audio Programming", taught by [Dr Andrew McPherson](http://instrumentslab.org) in the [School of Electronic Engineering and Computer Science](http://www.eecs.qmul.ac.uk). The module is offered on degree programmes including:

* [MSc in Sound and Music Computing](https://www.qmul.ac.uk/postgraduate/taught/coursefinder/courses/129308.html), a one-year Master's programme
* [PhD in Artificial Intelligence and Music](http://www.aim.qmul.ac.uk), a 4-year PhD programme with fully-funded studentships for UK and international students

## Recommended materials

Running the examples in this course assumes that you have a [Bela Starter Kit](https://shop.bela.io/products/bela-starter-kit) or [Bela Mini Starter Kit](https://shop.bela.io/products/bela-mini-starter-kit).

No external components are required for this lecture.

## Additional references

* A very helpful tutorial on the phase vocoder is [Pitch Shifting Using the Fourier Transform](http://blogs.zynaptiq.com/bernsee/pitch-shifting-using-the-ft/) by Stephan M. Bernsee. The approach to frequency detection in this lecture is based in part on this resource.
* [Table of window function details](https://vru.vibrationresearch.com/lesson/tables-of-window-function-details/) from [VR University](vru.vibrationresearch.com) 

Additionally, here are some textbooks and other resources related to the Fast Fourier Transform and spectral audio processing:

* Alan V. Oppenheim and Ronald W. Shafer, *Discrete-Time Signal Processing*, 3rd edition. [Publisher link](http://www.pearsonhighered.com/product?ISBN=0131988425). See also the same class on [MIT OpenCourseware](https://ocw.mit.edu/courses/electrical-engineering-and-computer-science/6-341-discrete-time-signal-processing-fall-2005/).
* Julius O. Smith, [Mathematics of the Discrete Fourier Transform (DFT)](https://ccrma.stanford.edu/~jos/mdft/) (free online textbook).
* Julius O. Smith, [Spectral Audio Signal Processing](https://ccrma.stanford.edu/~jos/sasp/) (free online textbook).
* Joshua D. Reiss and Andrew McPherson, *Audio Effects: Theory, Implementation and Application*. [Publisher link](https://www.taylorfrancis.com/books/9780429097232).
* Richard Boulanger and Victor Lazzarini, editors, *The Audio Programming Book*. [Publisher link](https://mitpress.mit.edu/books/audio-programming-book)
* [A visual introduction to the Fourier transform](https://www.youtube.com/watch?v=spUNpyF58BY) on YouTube from 3Blue1Brown
* [Divide and Conquer: the FFT algorithm](https://www.youtube.com/watch?v=iTMn0Kt18tg) on YouTube from MIT OpenCourseWare (a mathematical explainer)
