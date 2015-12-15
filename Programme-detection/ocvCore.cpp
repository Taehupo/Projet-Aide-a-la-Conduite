#include <cv.h>
#include <highgui.h>

#include "ocvCore.hpp"

OcvCore::OcvCore(std::string _filename) // Constructeur
: fileName(_filename)
{
	capture = cvCaptureFromAVI(fileName.c_str()); //Ne prend pas les string, que les const char*
	if (!capture) {
		std::cerr << "Erreur de chargement ::capture" << std::endl;
		exit(EXIT_FAILURE);
	}
	std::cout << "video" << std::endl;

	frame = cvQueryFrame(capture); //On récupère la première image de la vidéo
	if (!frame) exit(EXIT_FAILURE);
	std::cout << "image" << std::endl;

	imgTracking=cvCreateImage(cvGetSize(frame), IPL_DEPTH_8U, 3);
	cvZero(imgTracking);

	cvNamedWindow("frame");//création d'une fenetre "frame"
}

OcvCore::~OcvCore()
{
	cvReleaseImage(&imgTracking);
	cvReleaseCapture(&capture);
	cvDestroyAllWindows();
}

void OcvCore::filter() //Applique le filtre sur l'image contenue dans frame
{
	imgGrayScale = cvCreateImage(cvGetSize(frame),8,1); //création de l'image
	cvCvtColor(frame, imgGrayScale, CV_BGR2GRAY); //Passage en gris
	cvThreshold(imgGrayScale, imgGrayScale, 100, 255, CV_THRESH_BINARY_INV); //Aff binaire N/B
}

void OcvCore::getNewFrame() // On recupère l'image suivante
{
	frame = cvQueryFrame(capture);
	if (!frame) exit(EXIT_FAILURE);
	frame=cvCloneImage(frame);
}

void OcvCore::showFrameWindow() // On affiche l'image dans une fenetre
{	
	cvShowImage("frame", frame);
}
