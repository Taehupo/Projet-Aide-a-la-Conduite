#include <cv.h>
#include <highgui.h>

#include "ocvCore.hpp"

/**
* Constructeur : celui-ci ne prend que des const char* et permet la création de la fenetre
*/
OcvCore::OcvCore(std::string _filename)
: fileName(_filename)
{
	capture = cvCaptureFromAVI(fileName.c_str()); 					// Ne prend pas les string, que les const char*
	if (!capture) {
		std::cerr << "Erreur de chargement ::capture" << std::endl;
		exit(EXIT_FAILURE);
	}
	std::cout << "video" << std::endl;

	frame = cvQueryFrame(capture);								 	// On récupère la première image de la vidéo
	if (!frame) exit(EXIT_FAILURE);
	std::cout << "image" << std::endl;

	imgTracking=cvCreateImage(cvGetSize(frame), IPL_DEPTH_8U, 3);
	cvZero(imgTracking);

	cvNamedWindow("frame");											// création d'une fenetre "frame"
}

/**
* Destructeur : Destruction de la fenetre et arret de la capture
*/
OcvCore::~OcvCore()
{
	cvReleaseImage(&imgTracking);
	cvReleaseCapture(&capture);
	cvDestroyAllWindows();
}

/**
* Cette fonction permet d'appliquer le filtre sur l'image dans le contenue de la fenetre
*/
void OcvCore::filter() 
{
	imgGrayScale = cvCreateImage(cvGetSize(frame),8,1); 						// création de l'image
	cvCvtColor(frame, imgGrayScale, CV_BGR2GRAY); 								// Passage en gris
	cvThreshold(imgGrayScale, imgGrayScale, 100, 255, CV_THRESH_BINARY_INV); 	// Aff binaire N/B
}

/**
* Cette fonction permet de récuperer l'image suivante
*/
void OcvCore::getNewFrame() 
{
	frame = cvQueryFrame(capture);
	if (!frame) exit(EXIT_FAILURE);
	frame=cvCloneImage(frame);
}

/**
* Cette fonction permet l'affichage de l'image dans la fenetre
*/
void OcvCore::showFrameWindow() 
{	
	cvShowImage("frame", frame);
}
