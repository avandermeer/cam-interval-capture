#include "ofThread.h"
#include "ofTimer.h"

class Scheduler : public ofThread {
public:

	void init(ofVideoGrabber * vg, int interval) {
		timer.setPeriodicEvent(interval * 1000000); //miliseconds to nanoseconds
		vidGrabber = vg;
		startThread();
	}

private:
	ofTimer timer;
	ofVideoGrabber * vidGrabber;

	void threadedFunction() {
	
		while (isThreadRunning()) {
			timer.waitNext();
			// Do your thing here. It will run once per second.
			vidGrabber->update();
			if (vidGrabber->isFrameNew()) {

				lock();

				ofPixels & pixels = vidGrabber->getPixels();
				ofSaveImage(pixels, "SAVEDIMAGE_" + ofGetTimestampString() + ".jpg");
				unlock();
			}
		}
	}
};