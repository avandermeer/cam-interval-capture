#pragma once

#include "ofMain.h"
#include "Scheduler.h"


class ofApp : public ofBaseApp {

public:

	void setup();
	void update();

	ofVideoGrabber vidGrabber;
	int camWidth;
	int camHeight;

	Scheduler scheduler;

	vector<string> arguments;
};