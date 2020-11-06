/*
 ____  _____ _        _    
| __ )| ____| |      / \   
|  _ \|  _| | |     / _ \  
| |_) | |___| |___ / ___ \ 
|____/|_____|_____/_/   \_\

http://bela.io

C++ Real-Time Audio Programming with Bela - Lecture 17: Block-based processing
*/

// This file implements a browser-based GUI using p5.js
// It draws a spectrum of the signal received from the Bela program
// It is based on the Bela example 'Gui/frequency-response' which has
// a number of additional features and controls.

var guiSketch = new p5(function( p ) {
	var sampleRate = 44100;

	p.setup = function() {
		p.createCanvas(window.innerWidth, window.innerHeight);
		p.colorMode(p.RGB, 1);
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
		var dbRange = 50;
		var freqRange = 1; 
		var freqMin = 0;
		
		// Draw a line for each of the buffers received
		for(let k in buffers)
		{
			p.noFill();
			var rem = k % 3;
			var color = p.color(0 == rem, 1 == rem, 2 == rem);
			p.stroke(color);
			p.beginShape();
			let buf = buffers[k];
			for (let i = 0; i < fftSize && i < buf.length; i++) {
				var y;
				y = (1/dbRange * (20*(Math.log10(buf[i])) - zeroDbPos * dbRange) + 1);
				x = i / freqRange / fftSize + freqMin / (sampleRate/2);
				p.vertex(p.windowWidth * x, p.windowHeight * (1 - y));
			}
			p.endShape();
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
			p.text(txt, 60, yPos * p.windowHeight + 10);
		}

		// Draw X grid
		for(let x = 0.1; x <= 1; x += 0.1)
		{
			var val = freqRange * (x * sampleRate/2 - freqMin) / 1000;
			if(val < 0 || val > sampleRate / 2000)
				continue;
			p.stroke(0, 0, 0, 0.3);
			p.strokeWeight(0.2);
			p.line(x * p.windowWidth, 0, x * p.windowWidth, p.windowHeight);
			txt = val.toFixed(1) + "kHz";
			p.noStroke();
			p.fill(0);
			p.text(txt, x * p.windowWidth, 10);
		}
	}

	p.windowResized = function() {
		p.resizeCanvas(window.innerWidth, window.innerHeight);
	}
}, 'gui');
