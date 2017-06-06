#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
	fpscounter = 0;
	prevFpsMilis = 0;
	lastInterFrameTime = 20;


	ofSetFrameRate(1000); //240




	//set width
	if (arguments.size() > 2) {
		camWidth = atoi(arguments[2].c_str());
	}
	else {
	res_x_select:

		printf("Wat is de horizontale resolutie (width)?");
		std::cin >> camWidth;
		if (!cin) // or if(cin.fail())
		{
		// user didn't input a number
		cin.clear(); // reset failbit
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //skip bad input
		goto res_x_select;															   // next, request user reinput
		}
	}

	//set height
	if (arguments.size() > 3) {
		camHeight = atoi(arguments[3].c_str());
	}
	else {

	res_y_select:

		printf("Wat is de verticale resolutie (height)?");
		std::cin >> camHeight;
		if (!cin) // or if(cin.fail())
		{
			// user didn't input a number
			cin.clear(); // reset failbit
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //skip bad input
			goto res_y_select;															   // next, request user reinput
		}

	}

	//camWidth = 640;  // try to grab at this size.
	//camHeight = 480;

	//get back a list of devices.
	vector<ofVideoDevice> devices = vidGrabber.listDevices();


	for (int i = 0; i < devices.size(); i++) {
		if (devices[i].bAvailable) {
			//log the device
			ofLogNotice() << devices[i].id << ": " << devices[i].deviceName;
		}
		else {
			//log the device and note it as unavailable
			ofLogNotice() << devices[i].id << ": " << devices[i].deviceName << " - unavailable ";
		}
	}


	int deviceId;
	if (devices.size() == 1) {
		deviceId = 0;
	}
	else {
	device_select:

		printf("Multiple devices found- please enter index:(0-");
		cout << devices.size() - 1;
		printf(")");
		std::cin >> deviceId;
		if (!(deviceId >= 0 && deviceId < devices.size()))
		{
			printf("Wrong input\n");
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<streamsize>::max(), '\n');
			goto device_select;

		}
	}


	int interval = 333333333;//in nanoseconds
	//int interval = 300000000;//in nanoseconds
	if (arguments.size() > 1) {
		interval = atoi(arguments[1].c_str());
		interval = interval * 1000000;
	}

	printf("interval: ");
	cout << interval;
	printf("ms\n");
	printf("");
	printf("Press Ctrl+C to exit this program");


	vidGrabber.setUseTexture(false);
	vidGrabber.setDeviceID(deviceId);

	vidGrabber.setup(camWidth, camHeight, false);
	//vidGrabber.setDesiredFrameRate(3);
	vidGrabber.setUseTexture(false);
	vidGrabber.videoSettings();


	scheduler.init(&vidGrabber, interval, &lastInterFrameTime);

	start = ofGetElapsedTimeMillis();
	prevSec = 0;

}

void ofApp::update() {
	//cout << ofGetTimestampString("%i")<<"\n";

		
	if ((ofGetElapsedTimeMillis() - start) / 1000 > prevSec){
		if (ofGetElapsedTimeMillis() - start > 1000) { //delen door nul is niet oké
			cout << fpscounter / ((ofGetElapsedTimeMillis()-start) / 1000) << "fps \n";
		}
		
		//fpscounter = 0;
	}
	prevSec = (ofGetElapsedTimeMillis() - start) / 1000;

	//if (!scheduler.active) { //only update if thread is not active
	scheduler.lock();
		vidGrabber.update();
		if (vidGrabber.isFrameNew()) {


			int now = std::stoi(ofGetTimestampString("%i"));
			int timeDiff = now - prevFpsMilis;
			if (timeDiff <= 0) {
				timeDiff = 1000 - prevFpsMilis + now;
			}
			lastInterFrameTime = lastInterFrameTime + timeDiff;
			//cout << timeDiff << " | " << prevFpsMilis << ", " << now << " | " << lastInterFrameTime << "\n";
			prevFpsMilis = std::stoi(ofGetTimestampString("%i"));


			fpscounter = fpscounter + 1;

		}
		scheduler.unlock();
	//}
}
 


