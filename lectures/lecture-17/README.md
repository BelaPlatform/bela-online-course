# Lecture 17: Block-based processing

## [Watch Lecture 17 on YouTube](https://www.youtube.com/watch?v=2uyWn8P0CVg)

This lecture is the first of a two-part series on block-based processing, where audio is segmented into windows rather than processed one sample at a time. The most common use of block-based processing involves taking the Fast Fourier Transform (FFT) of windows of signal. This forms the basis of phase vocoder audio effects, which will be further discussed in the next lecture.

This lecture also covers the use of Bela's browser-based GUI to make responsive visualisations. The lecture shows how to send data from a Bela program to the GUI.

## What you'll learn in this lecture

* Generating and processing windows of a signal
* The Fast Fourier Transform (FFT)
* Sending data to the Bela GUI

## What you'll make in this lecture

* Two simple spectrum analysers with LEDs and GUI

## Code examples

**fft-led**: Simple project using the FFT to calculate high and low frequency content and blink LEDs. Also shows sending data to the Bela GUI.

**fft-circular-buffer**: Plot a real-time spectrum of the signal using the FFT. Your task is to implement the circular buffer code.

## About this course

This course is co-developed by Bela (Augmented Instruments Ltd) and Queen Mary University of London. The materials are based on a Master's module "Music and Audio Programming", taught by [Dr Andrew McPherson](http://instrumentslab.org) in the [School of Electronic Engineering and Computer Science](http://www.eecs.qmul.ac.uk). The module is offered on degree programmes including:

* [MSc in Sound and Music Computing](https://www.qmul.ac.uk/postgraduate/taught/coursefinder/courses/129308.html), a one-year Master's programme
* [PhD in Artificial Intelligence and Music](http://www.aim.qmul.ac.uk), a 4-year PhD programme with fully-funded studentships for UK and international students

## Recommended materials

Running the examples in this course assumes that you have a [Bela Starter Kit](https://shop.bela.io/products/bela-starter-kit) or [Bela Mini Starter Kit](https://shop.bela.io/products/bela-mini-starter-kit).

This lecture also uses several electronic components:

* Solderless breadboard ([Rapid](https://www.rapidonline.com/rapid-tp-039-solderless-breadboard-transparent-400-points-34-0671) | [Adafruit](https://www.adafruit.com/product/64))
* 2x LEDs (any colour) ([Rapid](https://www.rapidonline.com/kingbright-l-7113gd-5mm-2-2v-green-led-20mcd-55-0120) | [Adafruit](https://www.adafruit.com/product/298))
* 2x 220 ohm resistors ([Rapid](https://www.rapidonline.com/truohm-cr-025-220r-carbon-film-resistor-0-25w-pack-of-100-62-0354) | [Adafruit](https://www.adafruit.com/product/2780))
* Jumper wires ([Rapid](https://www.rapidonline.com/rapid-jw-003-breadboard-jumper-wires-bundle-of-75-34-0673) | [Adafruit](https://www.adafruit.com/product/153))

## Additional references

Here are some textbooks and other resources related to the Fast Fourier Transform and spectral audio processing:

* Alan V. Oppenheim and Ronald W. Shafer, *Discrete-Time Signal Processing*, 3rd edition. [Publisher link](http://www.pearsonhighered.com/product?ISBN=0131988425). See also the same class on [MIT OpenCourseware](https://ocw.mit.edu/courses/electrical-engineering-and-computer-science/6-341-discrete-time-signal-processing-fall-2005/).
* Julius O. Smith, [Mathematics of the Discrete Fourier Transform (DFT)](https://ccrma.stanford.edu/~jos/mdft/) (free online textbook).
* Julius O. Smith, [Spectral Audio Signal Processing](https://ccrma.stanford.edu/~jos/sasp/) (free online textbook).
* Joshua D. Reiss and Andrew McPherson, *Audio Effects: Theory, Implementation and Application*. [Publisher link](https://www.taylorfrancis.com/books/9780429097232).
* Richard Boulanger and Victor Lazzarini, editors, *The Audio Programming Book*. [Publisher link](https://mitpress.mit.edu/books/audio-programming-book)
* [A visual introduction to the Fourier transform](https://www.youtube.com/watch?v=spUNpyF58BY) on YouTube from 3Blue1Brown
* [Divide and Conquer: the FFT algorithm](https://www.youtube.com/watch?v=iTMn0Kt18tg) on YouTube from MIT OpenCourseWare (a mathematical explainer)
