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
// It is a simple sketch implementing two simulated LEDs,
// each controlled from the Bela program.

var guiSketch = new p5(function( sketch ) {

    let canvas_dimensions = [sketch.windowWidth, sketch.windowHeight];

    sketch.setup = function() {
        sketch.createCanvas(canvas_dimensions[0], canvas_dimensions[1]);
    };

    sketch.draw = function() {
        
        // Draw a black background with opacity
        sketch.background(0);
        
        // Retreive the data being sent from render.cpp
        let ledLow = Bela.data.buffers[0][0];
        let ledHigh = Bela.data.buffers[0][1];
     
    	// Draw two circles representing the LEDs
    	sketch.noStroke();
    	
    	// Low frequency
    	if(ledLow !== 0)
			sketch.fill(0, 255, 0);
		else
			sketch.fill(0, 50, 0);
		sketch.ellipse(sketch.windowWidth / 8, sketch.windowHeight / 8, sketch.windowWidth / 16, sketch.windowWidth / 16);
		
		// High frequency
    	if(ledHigh !== 0)
			sketch.fill(255, 0, 0);
		else
			sketch.fill(50, 0, 0);
		sketch.ellipse(sketch.windowWidth / 4, sketch.windowHeight / 8, sketch.windowWidth / 16, sketch.windowWidth / 16);
		
		// Text labels
		sketch.fill(255);
		sketch.textSize(sketch.windowWidth / 80);
		sketch.textFont('Helvetica');
		sketch.textAlign(CENTER);
		sketch.text('LOW', sketch.windowWidth / 8, sketch.windowHeight / 4);
		sketch.text('HIGH', sketch.windowWidth / 4, sketch.windowHeight / 4);
    };
    
}, 'gui');
