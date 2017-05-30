#include "ofThread.h"
#include "ofTimer.h"

class Scheduler : public ofThread {
public:

	void init(ofVideoGrabber * vg, int interval, int w, int h) {
		timer.setPeriodicEvent(interval); //miliseconds to nanoseconds
		vidGrabber = vg;
		startThread();
		width = w;
		height = h;
	}

private:
	ofTimer timer;
	ofVideoGrabber * vidGrabber;
	ofImage colorImg;
	int width;
	int height;

	void threadedFunction() {
	
		
		while (isThreadRunning()) {
			timer.waitNext();
			// Do your thing here. It will run at the set interval

			lock();

			int skippedFrames = 0;


				printf("new image found at: ");
				cout << ofGetTimestampString();
				printf("\n");
				ofPixels & pixels = vidGrabber->getPixels();
				string time = ofGetTimestampString();


				colorImg.setFromPixels(pixels);
				//colorImg.mirror(false, true);
				colorImg.setImageType(OF_IMAGE_GRAYSCALE);
				ofSaveImage(colorImg.getPixelsRef(), "SAVEDIMAGE_" + time + ".bmp");

				printf("saved at: ");
				cout << ofGetTimestampString();
				printf("\n");


		
			
			unlock();
		}
	}
};