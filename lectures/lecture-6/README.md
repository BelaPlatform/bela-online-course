# Lecture 6: Analog I/O

## [Watch Lecture 6 on YouTube](https://www.youtube.com/watch?v=I8vV7AsUc-Y)

This lecture explains how to work with analog input and output on Bela. This is the first lecture in the series to build external circuits, and it introduces the basics of working with solderless breadboards. After connecting the circuit, it shows how to create a voltage-controlled oscillator (VCO) and a simple musical instrument using a force-sensing resistor (FSR).

## What you'll learn in this lecture

* Analog inputs and outputs on Bela
* Working with breadboards
* Control voltages and VCOs

## What you'll make in this lecture

* A voltage-controlled oscillator and a simple instrument

## Code examples

**vco**: Voltage-controlled oscillator example. During the lecture this is converted from using the GUI sliders to using the analog inputs.

**vco-analog-out**: Extension of the `vco` project which includes a pulsating LED showing the beats between oscillators.

## About this course

This course is co-developed by Bela (Augmented Instruments Ltd) and Queen Mary University of London. The materials are based on a Master's module "Music and Audio Programming", taught by [Dr Andrew McPherson](http://instrumentslab.org) in the [School of Electronic Engineering and Computer Science](http://www.eecs.qmul.ac.uk). The module is offered on degree programmes including:

* [MSc in Sound and Music Computing](https://www.qmul.ac.uk/postgraduate/taught/coursefinder/courses/129308.html), a one-year Master's programme
* [PhD in Artificial Intelligence and Music](http://www.aim.qmul.ac.uk), a 4-year PhD programme with fully-funded studentships for UK and international students

## Recommended parts

Running the examples in this course assumes that you have a [Bela Starter Kit](https://shop.bela.io/products/bela-starter-kit) or [Bela Mini Starter Kit](https://shop.bela.io/products/bela-mini-starter-kit). Note that the analog outputs are only available on the original Bela board, and not on Bela Mini.

This lecture also uses several electronic components:

* Solderless breadboard ([Rapid](https://www.rapidonline.com/rapid-tp-039-solderless-breadboard-transparent-400-points-34-0671) | [Adafruit](https://www.adafruit.com/product/64))
* 3x 10k potentiometers ([Rapid](https://www.rapidonline.com/taiwan-alpha-rv16af-10k-lin-16mm-metal-case-pcb-potentiometer-65-0715) | [Adafruit](https://www.adafruit.com/product/4133))
* 1x force-sensing resistor ([Rapid](https://www.rapidonline.com/taiwan-alpha-43mm-square-membrane-force-sensor-78-4008) | [Adafruit](https://www.adafruit.com/product/1075))
* 1x LED (any colour) ([Rapid](https://www.rapidonline.com/kingbright-l-7113gd-5mm-2-2v-green-led-20mcd-55-0120) | [Adafruit](https://www.adafruit.com/product/298))
* 1x 10k resistor ([Rapid](https://www.rapidonline.com/truohm-cr-025-10k-carbon-film-resistor-0-25w-pack-of-100-62-0394) | [Adafruit](https://www.adafruit.com/product/2784))
* 1x 220 ohm resistor ([Rapid](https://www.rapidonline.com/truohm-cr-025-220r-carbon-film-resistor-0-25w-pack-of-100-62-0354) | [Adafruit](https://www.adafruit.com/product/2780))
* Jumper wires ([Rapid](https://www.rapidonline.com/rapid-jw-003-breadboard-jumper-wires-bundle-of-75-34-0673) | [Adafruit](https://www.adafruit.com/product/153))

## Additional references

### Working with electronic circuits

* [Breadboards for beginners](https://learn.adafruit.com/breadboards-for-beginners/introduction) by Adafruit
* [Voltage divider tutorial](https://learn.sparkfun.com/tutorials/voltage-dividers/all) by SparkFun

### Sensors for audio and music

* [Introduction to potentiometers](https://sound-au.com/pots.htm) by Rod Elliott. Contains a deeper dive into the how and why of potentiometers, especially for audio.
* [SensorWiki](https://sensorwiki.org/doku.php) by the [Input Devices and Musical Interaction Laboratory](http://www-new.idmil.org) at McGill University. Surveys the sensors used in digital musical instruments.