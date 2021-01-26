/*
 ____  _____ _        _    
| __ )| ____| |      / \   
|  _ \|  _| | |     / _ \  
| |_) | |___| |___ / ___ \ 
|____/|_____|_____/_/   \_\

http://bela.io

C++ Real-Time Audio Programming with Bela - Lecture 19: Phase vocoder, part 2
*/

// This file implements a browser-based GUI using p5.js
// It draws a spectrum of the signal received from the Bela program
// It is based on the Bela example 'Gui/frequency-response' which has
// a number of additional features and controls.

function sendToBela()
{
	// this is the object for which the input has changed
	let value = this.value();
	if(typeof(value) === "string")
		value = parseFloat(value);
	if(isNaN(value)) {
		// this is required for the C++ parser to recognize it as a
		// number (NaN is not recognized as a number)
		value = 0;
	}
	clearTimeout(this.timeout);
	let obj = {};
	obj[this.guiKey] = value;

	// do not send right now: throttle to avoid ultra-fast changes
	this.timeout = setTimeout(function(obj) {
		console.log("Sending ", obj);
		Bela.control.send(obj);
	}.bind(null, obj), 1);
}

class GuiSlider {
	// obj needs to contain:
	//   label, position, slider
	// Additionally:
	//   shortLabel is optional, and if present will be sent to Bela when the slider value changes
	//   p5 is optional, and if present it will be used instead of the global one
	// slider value changes
	constructor(obj) {
		this.label = obj.label;
		this.position = obj.position;
		this.slider = obj.slider;
		if(obj.p5)
			this.p5 = obj.p5;
		else
			this.p5 = p5; // assuming there is such a global object
		if(obj.shortLabel) {
			// set up action for when the parameter changes
			this.slider.guiKey = obj.shortLabel;
			this.slider.input(sendToBela);
			this.slider.timeout = undefined;
			// call the callback now to sync the running program to the GUI
			sendToBela.call(this.slider);
		}
	}
	draw() {
		this.p5.push();
		this.p5.noStroke();
		this.p5.fill(0);
		var textY = this.position[1] + 15;
		var sliderX = this.position[0] + 80;
		// labels
		this.p5.text(this.label, this.position[0], textY);
		// slider
		this.slider.position(sliderX, this.position[1]);
		// value
		// + 60 is a bug workaround
		this.p5.text(this.slider.value().toFixed(3), sliderX + 60 + this.slider.width, textY);
		this.p5.pop();
	}
	// can this be done more elegantly?
	value(arg) {
		if(arg)
			return this.slider.value(arg);
		return this.slider.value();
	}
}

var guiSketch = new p5(function( p ) {
	var sampleRate = 44100;
	var controlsXOff = 330;
	var controlsYOff = 200;
	var slidersSpacing = 30;
	var oscillatorFreqSlider; 		// Slider to change frequency

	p.setup = function() {
		p.createCanvas(window.innerWidth, window.innerHeight);
		p.colorMode(p.RGB, 1);
		
		// Create a slider to change oscillator frequency
		var slider = p.createSlider(50, 5000, (10.0 * 44100 / 1024), 0.001);
		oscillatorFreqSlider = new GuiSlider({
				label: "Oscillator frequency",
				shortLabel: "oscfreq",
				position: [p.windowWidth - controlsXOff, p.windowHeight - controlsYOff],
				slider: slider,
				p5: p,
		});
	}

	p.draw = function() {
		// Get the data buffer(s) from the Bela C++ program
		var buffers = Bela.data.buffers;
		
		// Check if any data has been received
		if(!buffers.length)
			return;

		p.background(255);	// white background

		var fftSize = buffers[0].length;	// This gives the FFT size
		var fftSizeLog = Math.log(fftSize);
		p.strokeWeight(1);
		var zeroDbPos = 0.5;
		var dbRange = 100;
		var freqRange = 1; 
		var freqMin = 0;
		var xOffset = 50;
		var detectedFrequency = 0;
		var maxBinIndex = -1;
		
		// Draw a line for the spectrum in the first buffer
		p.noFill();
		var color = p.color(1, 0, 0);
		p.stroke(color);
		p.beginShape();
		let buf = buffers[0];
		for (let i = 0; i < fftSize && i < buf.length; i++) {
			var y;
			y = (1/dbRange * (20*(Math.log10(buf[i])) - zeroDbPos * dbRange) + 1);
			x = i / freqRange / fftSize + freqMin / (sampleRate/2);
			p.vertex(p.windowWidth * x + xOffset, p.windowHeight * (1 - y));
		}
		p.endShape();
		
		// Numerical analysis is in the second buffer
		if(buffers.length >= 2) {
			if(buffers[1].length > 0) {
				maxBinIndex = buffers[1][0];
			}
			if(buffers[1].length > 1) {
				detectedFrequency = buffers[1][1];
			}
		} 

		// Draw Y grid
		for(let y = -1; y <= 2; y += 0.1)
		{
			p.stroke(0, 0, 0, 0.3);
			p.strokeWeight(0.2);
			var yPos = y + zeroDbPos;
			var txt = (-dbRange * yPos + dbRange * zeroDbPos).toFixed(1)+'dB';
			p.line(0, yPos * p.windowHeight, p.windowWidth, yPos * p.windowHeight);
			p.noStroke();
			p.fill(0);
			p.text(txt, xOffset, yPos * p.windowHeight + 10);
		}

		// Draw X grid
		for(let x = 0.1; x <= 1; x += 0.1)
		{
			var val = freqRange * (x * sampleRate/2 - freqMin) / 1000;
			if(val < 0 || val > sampleRate / 2000)
				continue;
			p.stroke(0, 0, 0, 0.3);
			p.strokeWeight(0.2);
			p.line(x * p.windowWidth + xOffset, 0, x * p.windowWidth + xOffset, p.windowHeight);
			txt = val.toFixed(1) + "kHz";
			p.noStroke();
			p.fill(0);
			p.text(txt, x * p.windowWidth + xOffset, 10);
		}
		
		// Draw controls
		oscillatorFreqSlider.draw();
		
		// Label detected frequency
		p.noStroke();
		p.fill(0);
		txt = "Detected frequency: " + detectedFrequency.toFixed(2) + "Hz";
		p.text(txt, p.windowWidth - controlsXOff, p.windowHeight - controlsYOff + 40);
		txt = "Max FFT bin: " + maxBinIndex;
		p.text(txt, p.windowWidth - controlsXOff, p.windowHeight - controlsYOff + 60);
	}

	p.windowResized = function() {
		p.resizeCanvas(window.innerWidth, window.innerHeight);
	}
}, 'gui');
