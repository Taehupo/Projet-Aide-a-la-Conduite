#include <cv.h>
#include <highgui.h>
#include <stdio.h>
#include <time.h>
#include <chrono>
#include <ctime>
#include <ratio>

#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

using namespace std;
using namespace std::chrono;
using namespace cv;

#include "laneDetection.hpp"
#include "ocvCore.hpp"

int main(int argc, char const *argv[])
{
	// Revue proto2
		/*
			Initialisations
		*/	
		CvFont font;

		OcvCore *chaud = new OcvCore("b.mp4"); // la !

	  	cvInitFont(&font,CV_FONT_HERSHEY_SIMPLEX, 1,1); // Initialisation de la police d'écriture
		int i=0;
	  	int temps = 15; // temps d'attente entre deux frames
	    
	    cvNamedWindow("Control", CV_WINDOW_AUTOSIZE); // barettes de contrôle HSV
	    
	    IplImage* frame=0; //Contiendra une image de la vidéo
	    Mat frameCPP;
	    
	    //Chargement de la vidéo
	    VideoCapture captureCPP ("b.mp4"); // modif new main


	    if(!captureCPP.isOpened())
	    {
	        cout << "Impossible d'ouvrir la video.  ** exit(-1) **";
    		return -1;
	    }
	    captureCPP >> frameCPP; //On recup une frame

	    //frame = cvQueryFrame(capture); //On charge une frame       
	    //if(!frame) return -1;
	   
	    //create a blank image and assigned to 'imgTracking' which has the same size of original video
	    Mat imgTrackingCPP (frameCPP.size(), CV_8UC3, Scalar(0));

	    chaud->setImgTracking(cvCreateImage(frameCPP.size(),IPL_DEPTH_8U, 3));
	    	// tous ce qui est imgTracking devient chaud.getImgTracking()
	    
	    //cvZero(imgTracking); //passage en n&b

			
		//Paramètres du filtre HSV
		int iLowH = 172;
		int iHighH = 179;

		int iLowS = 51; 
		int iHighS = 255;

		int iLowV = 66;
		int iHighV = 255;

		//Création des barettes de réglage du filtre HSV
		cvCreateTrackbar("LowH", "Control", &iLowH, 179); //Hue (0 - 179)
		cvCreateTrackbar("HighH", "Control", &iHighH, 179);

		cvCreateTrackbar("LowS", "Control", &iLowS, 255); //Saturation (0 - 255)
		cvCreateTrackbar("HighS", "Control", &iHighS, 255);

		cvCreateTrackbar("LowV", "Control", &iLowV, 255); //Value (0 - 255)
		cvCreateTrackbar("HighV", "Control", &iHighV, 255);
		
		while(true){
		//cout << i << endl;
		frame = cvQueryFrame(capture);
		if(!frame) break;
		frame=cvCloneImage(frame); 

		//converting the original image into grayscale
		IplImage* imgGrayScale = cvCreateImage(cvGetSize(frame), 8, 1); 
		cvCvtColor(frame,imgGrayScale,CV_BGR2GRAY);

		//thresholding the grayscale image to get better results
		cvThreshold(imgGrayScale,imgGrayScale,100,255,CV_THRESH_BINARY_INV); // Inversion binaire (NOIR/BLANC)

		cvShowImage("NB", imgGrayScale); //Affichage de l'image dans une fenetre

		/*
			Détection des cercles
		*/
		

		Mat imgOriginal = cvarrToMat(frame);
		Mat dessins = imgOriginal.clone();
		Mat imgHSV;
		cvtColor(imgOriginal, imgHSV, COLOR_BGR2HSV); //Conversion BGR -> HSV

		Mat imgThresholded;
		
		//Tresholding avec le filtre HSV
		inRange(imgHSV, Scalar(iLowH, iLowS, iLowV), Scalar(iHighH, iHighS, iHighV), imgThresholded); //Threshold the image
		
		//Puissance de la morpho
		int morpho = 3;

		//ouverture morpho
		erode(imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(morpho, morpho)) );
		dilate( imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(morpho, morpho)) ); 

		//fermeture morpho
		dilate( imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(morpho, morpho)) ); 
		erode(imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(morpho,  morpho)) );

		//stockage des cercles
		vector<Vec3f> circles;

		//On détecte les cercles
		HoughCircles( imgThresholded, circles, CV_HOUGH_GRADIENT, 1, imgThresholded.rows/8, 200, 25, 10, 50 );

		//Affichage des cercles
		for( size_t i = 0; i < circles.size(); i++ )
		{
			Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
			int radius = cvRound(circles[i][2]);
			// circle center
			cvCircle( frame, center, 3, Scalar(0,255,0), -1, 8, 0 );
			// circle outline
			cvCircle( frame, center, radius, Scalar(0,0,255), 3, 8, 0 );
		}
		// !!!!!!!!!!!!!!!!!! //
		trackObject(imgGrayScale, i, temps); // Recherche et affichage de tout les contours
		
		bool grid=false; //Afficher la grille : je sais pas s'il a une place dans le code mais mieux le vaut ici
		if (grid) traceGrille(*chaud->getImgTracking());

		//Affichage de la vidéo sur l'écran
		cvPutText (*chaud->getImgTracking(),doubleToStr(int(moyenne_vitesseT)).c_str(),cvPoint(40,30), &font, cvScalar(0,(moyenne_vitesseT<=110)?255:0,(moyenne_vitesseT>110)?255:0)); //Affichage de la vitesse BGR
		if (moyenne_vitesseT>110) panneau(5,30);
		// Add the tracking image and the frame
		cvAdd(frame, *chaud->getImgTracking(), frame); //On superpose les deux pour faire apparaitre les points

		cvSaveImage("test.jpg", frame); //Sortie de l'image
		imshow("Thresholded Image", imgThresholded); //show the thresholded image
		cvShowImage("Video", frame);
		
		
		/*
			Gestion des events
		*/
		
		
		int c = cvWaitKey(temps);//15 30 30 30

		if ((char)c==72 || (char)c==104) cvSaveImage("test2.jpg", frame);


		/*Pas toucher début*/
        //Wait 10mS

        if ((char)c=='g' || (char)c=='G') grid=!grid; //affichage de la grille
        if ((char)c=='m') temps = 100; //accéléré
        if ((char)c=='l') temps =15; //vitesse normale
        if ((char)c=='p') temps =1; //ralentis
        if ((char)c=='o') temps =0; //pause ou pas à pas
        if((char)c==27 ) break;

        /*Pas troucher fin*/
        
        /*
        	Nettoyage
        */        
        
        cvZero(*chaud->getImgTracking()); // Supprimer les autres points

		//Clean up used images
		cvReleaseImage(&imgGrayScale); // destruction des images         
		cvReleaseImage(&frame);
        
    }

    cvDestroyAllWindows();
    cvReleaseImage(&chaud->getImgTracking());
    cvReleaseCapture(&capture); 

	// Avant revu proto2
	//	std::cout << "Lancement" << std::endl;

	//	OcvCore* core = new OcvCore ("v.mp4");

	//	while (true) {
	//		core->showFrameWindow();
	//		core->getNewFrame();

		//	int c = cvWaitKey(10);//15
	    //    //If 'ESC' is pressed, break the loop
	    //    if((char)c==27 ) break;
	//	}

	//	cvDestroyAllWindows();
	//	delete core;

		return 0;
}
