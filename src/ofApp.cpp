#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
	ofSetFrameRate(1000);


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


	vidGrabber.setUseTexture(false);
	vidGrabber.setDeviceID(deviceId);
	vidGrabber.setDesiredFrameRate(60);
	vidGrabber.setup(camWidth, camHeight, false);
	vidGrabber.setUseTexture(false);

	int interval = 300;
	if (arguments.size() > 1) {
		interval = atoi(arguments[1].c_str());
	}

	printf("interval: ");
	cout << interval;
	printf("ms\n");
	printf("");
	printf("Press Ctrl+C to exit this program");

	scheduler.init(&vidGrabber, interval);  



}



