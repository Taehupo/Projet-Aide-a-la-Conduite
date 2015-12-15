#include <iostream>

#include "laneDetection.hpp"
#include "ocvCore.hpp"

int main(int argc, char const *argv[])
{
	std::cout << "Lancement" << std::endl;

	OcvCore* core = new OcvCore ("v.mp4");

	while (true) {
		core->showFrameWindow();
		core->getNewFrame();

		int c = cvWaitKey(10);//15
        //If 'ESC' is pressed, break the loop
        if((char)c==27 ) break;
	}

	cvDestroyAllWindows();
	delete core;

	return 0;
}
