#include "ofMain.h"
#include "ofApp.h"

#define DISPLAY_MODE OF_WINDOW // Can be OF_WINDOW or OF_FULLSCREEN

int main() { // Adapted from OF-SNAKE MP: https://github.com/uiuc-sp18-cs126/of-snake-ElizWang
	//ofSetupOpenGL(640, 480, DISPLAY_MODE); // setup the GL context
    ofSetupOpenGL(780, 740, DISPLAY_MODE); // setup the GL context
	ofSetFrameRate(5);	
	ofRunApp(new PacmanGame());
}
