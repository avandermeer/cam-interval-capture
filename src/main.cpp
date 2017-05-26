#include "ofMain.h"
#include "ofApp.h"
#include "ofAppNoWindow.h"


//========================================================================
int main(int argc, char *argv[]){

	printf("Webcam Picture\n");
	printf("==============\n");
	printf("Developed by Albert van der Meer\n");
	printf("\n");


	ofAppNoWindow window;
	ofSetupOpenGL(&window, 0, 0, OF_WINDOW);


	ofApp *app = new ofApp();
	app->arguments = vector<string>(argv, argv + argc);
	ofRunApp(app); // start the app
	

}
