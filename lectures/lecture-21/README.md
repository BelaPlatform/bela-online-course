# Lecture 21: ARM assembly language

## [Watch Lecture 21 on YouTube](https://www.youtube.com/watch?v=KhcvpemjQyo)

This lecture introduces working with assembly language on ARM processors, including the ARM Cortex-A8 found in Bela. It explains the basic operations of the CPU, the format of assembly language instructions and how to call them from C or C++. It also explains how to work with floating point numbers in assembly, setting the stage for high-performance filtering in Lecture 22.

## What you'll learn in this lecture

* Basics of assembly language instructions on ARM
* Calling assembly language code from C++
* Floating point in assembly language

## What you'll make in this lecture

* Example functions written in assembly

## Code examples

**asm-test**: Template project for creating basic functions in assembly language.

**asm-factorial**: Implement a factorial function in assembly language and compare the results to the same thing written in C.

**asm-float**: Shows how to work with floating point numbers in assembly language.

## About this course

This course is co-developed by Bela (Augmented Instruments Ltd) and Queen Mary University of London. The materials are based on a Master's module "Music and Audio Programming", taught by [Dr Andrew McPherson](http://instrumentslab.org) in the [School of Electronic Engineering and Computer Science](http://www.eecs.qmul.ac.uk). The module is offered on degree programmes including:

* [MSc in Sound and Music Computing](https://www.qmul.ac.uk/postgraduate/taught/coursefinder/courses/129308.html), a one-year Master's programme
* [PhD in Artificial Intelligence and Music](http://www.aim.qmul.ac.uk), a 4-year PhD programme with fully-funded studentships for UK and international students

## Recommended materials

Running the examples in this course assumes that you have a [Bela Starter Kit](https://shop.bela.io/products/bela-starter-kit) or [Bela Mini Starter Kit](https://shop.bela.io/products/bela-mini-starter-kit).

No external components are required for this lecture.

## Additional references

* [ARM instruction set quick reference card](https://users.ece.utexas.edu/~valvano/Volume1/QuickReferenceCard.pdf). Handy PDF featuring summaries of the instructions on most ARM processors.
* [VFP instruction set quick reference card](https://www.cse.scu.edu/~dlewis/book3/docs/Vector_Floating_Point_Instruction_Set.pdf). PDF reference for the instruction set on the Vector Floating Point unit. Note: you will find different versions of this instruction set, some with VFP instructions preceded by `V` (as it is here), others with instructions preceded by `F`. Which one to use may depend on the specific version of the assembler.
* [ARM Cortex-A8 technical reference manual](https://developer.arm.com/documentation/ddi0344/k). This is the complete technical information on the operation of the ARM Cortex-A8 CPU, including its instruction set and its floating point units.

