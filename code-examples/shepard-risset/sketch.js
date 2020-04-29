let w;
let phase = 0;
let speed = 1;

function setup() {
	//Create a canvas of dimensions given by current browser window
	createCanvas(windowWidth, windowHeight);
	angleMode(DEGREES);
	// w is used for drawing bars off screen
	w = sqrt(width * width + height * height)*1.5;

}

function draw() {

	background(255);

	// Retrieve the data being sent from render.cpp
	let numOscillators = Bela.data.buffers[0] * 2;
	let cycleTime = Bela.data.buffers[1];

	speed = map(cycleTime, 0.1, 5.0, 7, 0.5);

	// Draw the lines, rotate and then animate position
	push();

	translate(width / 2, height / 2);　
	rotate(60);
	translate(-w / 2, -w / 2);
	phase += speed;
	for (let i = 0; i < numOscillators; i++)
	{

		x = w - ((i / numOscillators * w + phase) % w);

		if (i % 2 === 0) {
			stroke(198,	28,	15);
		} else {
			stroke(0, 33, 153);
		}
		strokeWeight(w / (numOscillators*2));
		line(x, 0, x, w);
	}

	pop();

	// Masking boxes
	fill(0);
	noStroke();
	rect(0, 0, width, height*0.2);
	rect(0, height*0.8, width, height);
	rect(0, 0, width*0.4, height);
	rect(width*0.6, 0, width, height);

	// Text
	textAlign(CENTER);
	textSize(24);
	stroke(255);
	strokeWeight(1);
	fill(255);
	text("MOVE MOUSE VERTICALLY\nTO CHANGE SPEED", width / 2, height - (height*0.1));

}

function windowResized() {
	resizeCanvas(windowWidth, windowHeight);
}

function mouseMoved() {
	//Sends to render.cpp a buffer. First argument is buffer index, second one is data type and third one is data sent.
	//In this case we send an array with two elements.
	Bela.data.sendBuffer(0, 'float', [mouseX/width, 1 - mouseY/height]);
}
