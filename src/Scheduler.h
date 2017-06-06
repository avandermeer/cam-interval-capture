#include "ofThread.h"
#include "ofTimer.h"
#include <string> 

class Scheduler : public ofThread {
public:
	bool active;

	void init(ofVideoGrabber * vg, int interval, int * lIFT){
		timer.setPeriodicEvent(interval); //miliseconds to nanoseconds
		vidGrabber = vg;
		startThread();
		lastInterFrametime = lIFT;
	}

private:
	ofTimer timer;
	ofVideoGrabber * vidGrabber;
	ofImage colorImg;
	int * lastInterFrametime;
	int highestFrameTime;

	void threadedFunction() {
	
		
		while (isThreadRunning()) {
			timer.waitNext();
			// Do your thing here. It will run at the set interval

			lock();
			active = true;

			int skippedFrames = 0;



				ofPixels & pixels = vidGrabber->getPixels();
				string time = ofGetTimestampString();


				colorImg.setFromPixels(pixels);
				//colorImg.mirror(false, true);
				colorImg.setImageType(OF_IMAGE_GRAYSCALE);
							
					

				ofSaveImage(colorImg.getPixelsRef(), "SAVEDIMAGE_" + time + "--"+ std::to_string(*lastInterFrametime) + ".bmp");


				printf("New image saved at: ");
				cout << ofGetTimestampString();
				cout << "| name: SAVEDIMAGE_" << time << "--" << std::to_string(*lastInterFrametime) << ".bmp";
				cout << "\n";
				

				*lastInterFrametime = 0;

		
				active = false;
			unlock();
		}
	}
};