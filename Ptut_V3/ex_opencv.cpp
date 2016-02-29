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

IplImage* imgTracking=0;

//paramètres de la police
CvFont font;
double hScale=1.0;
double vScale=1.0;
int    lineWidth=1;

bool grid=false; //Afficher la grille ?

typedef struct {
	CvPoint points[4];
	int posX, posY;
	bool utilisee = false;
} S_Ligne;

int lastX1 = -1;
int lastY1 = -1;

int lastX2 = -1;
int lastY2 = -1;

double moyenne_vitesse = 1;
double moyenne_vitesse2 = 1;
double moyenne_vitesseT = 1;

duration<double> time_span;
high_resolution_clock::time_point t12, t22;

double vitesse_lue;
double avg = 100;
float taille_ligne = 13;


unsigned int readArea [3];

const string doubleToStr(double x){
	stringstream ss;
	ss << x;
	return ss.str();
}

double distance2pt (CvPoint* p0, CvPoint* p1) { //Distance entre deux points
	return sqrt(pow(p0->x - p1->x, 2) + pow(p0->y - p1->y,2));
}

S_Ligne ligne_tab[2];

double centrey = 300; // Position initiale du centre (entre deux lignes)

void swapCvPoint (CvPoint * p1, CvPoint * p2) {
	CvPoint tmp = *p1;
	*p1 = *p2;
	*p2 = tmp;
}

bool ligne (CvPoint *pt[4]) {

	double taille[4];
	taille[0] = distance2pt(pt[0], pt[1]);
	taille[1] = distance2pt(pt[1], pt[2]);
	taille[2] = distance2pt(pt[2], pt[3]);
	taille[3] = distance2pt(pt[3], pt[0]);
	
	if (taille[0]<taille[1])
	{
		int tmp = taille[0];
		taille[0]=taille[1];
		taille[1]=tmp;
	}
	
	return taille[2]>0,75*taille[3];
	
	/*
	for (uint i=0; i<2; ++i)
	{		
		if (pt[0]>pt[1])
			swapCvPoint(pt[0], pt[1]);
		if (pt[2]>pt[3])
			swapCvPoint(pt[2], pt[3]);
		if (pt[1]>pt[2])
			swapCvPoint(pt[2], pt[1]);
	}
	
	if (distance2pt[])
	*/
}

void trackObject(IplImage* imgThresh, int& ni, const int & temps){ //track the possition of the ball
	CvSeq* contour;  //Pointeur vers un contour
	CvSeq* result;   //hold sequence of points of a contour
	CvMemStorage *storage = cvCreateMemStorage(0); //storage area for all contours

	//Recherche de tout les contours de l'image
	cvFindContours(imgThresh, storage, &contour, sizeof(CvContour), CV_RETR_LIST, CV_CHAIN_APPROX_SIMPLE, cvPoint(0,0));
	
	uint lignePos = 0; // Position de la ligne 0 = gauche 1 = droite


	//On passe sur tout les contours
	while(contour)
	{
		//obtain a sequence of points of the countour, pointed by the variable 'countour'
		result = cvApproxPoly(contour, sizeof(CvContour), storage, CV_POLY_APPROX_DP, cvContourPerimeter(contour)*0.02, 0);

		//if there are 3 vertices  in the contour and the area of the triangle is more than 100 pixels
		if(result->total==4 && fabs(cvContourArea(result, CV_WHOLE_SEQ))>100 ) // Détection des lignes (4 cotés) et aire > 100
		{
			CvPoint *pt[4];
			for(int i=0;i<4;i++) // Récupération des coordonnées
			{
				pt[i] = (CvPoint*)cvGetSeqElem(result, i);
			}

			int posX=( pt[0]->x + pt[1]->x + pt[2]->x +pt[3]->x )/4; // centre des points
			int posY=( pt[0]->y + pt[1]->y + pt[2]->y +pt[3]->y )/4;

			if (posY>400 ) //Si en bas de l'écran et proche de la moyenne (&& (posX>centrey-100 || posX<centrey+100))
			{ 
				centrey = (ligne_tab[1].posX + ligne_tab[0].posX + posX)/3; //Calcul du centre entre les lignes | . |
				bool ligne_ = false;
				if (posX<centrey )//ligne à gauche (&& posX>centrey-200)
				{ 
					lignePos = 0;
					ligne_ = true;
				}
				else if (posX>centrey) //ligne à droite de l'écran ( && posX<centrey+200)
				{ 
					lignePos = 1;
					ligne_ = true;
				} 
				
				if (ligne_)
				{
					//Sauvegarde des points
					ligne_tab[lignePos].utilisee = true;

					ligne_tab[lignePos].points[0].x = pt[0]->x;
					ligne_tab[lignePos].points[0].y = pt[0]->y;
					ligne_tab[lignePos].points[1].x = pt[1]->x;
					ligne_tab[lignePos].points[1].y = pt[1]->y;
					ligne_tab[lignePos].points[2].x = pt[2]->x;
					ligne_tab[lignePos].points[2].y = pt[2]->y;
					ligne_tab[lignePos].points[3].x = pt[3]->x;
					ligne_tab[lignePos].points[3].y = pt[3]->y;
				
					//centre de la ligne
					ligne_tab[lignePos].posX = posX;
					ligne_tab[lignePos].posY = posY;
					//cout << "Aire : " << fabs(cvContourArea(result, CV_WHOLE_SEQ)) << endl; 
				}
			}

		} 
		else if(result->total==3 ) // Détection des triangles (3 cotés)
		{ 
			CvPoint *pt[3];
			
			for(int i=0;i<3;i++) //Récupération des coordonnées
			{
				pt[i] = (CvPoint*)cvGetSeqElem(result, i);
			}

			//Traçage des triangles
			if (distance2pt(pt[0], pt[1])<50 && distance2pt(pt[0], pt[1])>20 && 
			distance2pt(pt[1], pt[2])<50 && distance2pt(pt[1], pt[2])>20 &&
			distance2pt(pt[2], pt[0])<50 && distance2pt(pt[2], pt[0])>20 ) // On vérifie que les mesures correspondent à un panneau triangulaire (3 cotés entre 50 et 20 pix)
			{ 
				cvLine(imgTracking, *pt[0], *pt[1], cvScalar(255,0,0),4);
				cvLine(imgTracking, *pt[1], *pt[2], cvScalar(255,0,0),4);
				cvLine(imgTracking, *pt[2], *pt[0], cvScalar(255,0,0),4);
			}
		}



		//obtain the next contour
		contour = contour->h_next; 
	}
  
for (uint i=0; i<2; i++) //traçage des lignes
{
	if (ligne_tab[i].utilisee) 
	{
		cvLine(imgTracking, cvPoint(ligne_tab[i].points[0].x, ligne_tab[i].points[0].y), cvPoint(ligne_tab[i].points[1].x, ligne_tab[i].points[1].y), cvScalar(0,(i==1)?255:0,255),4);
		cvLine(imgTracking, cvPoint(ligne_tab[i].points[1].x, ligne_tab[i].points[1].y), cvPoint(ligne_tab[i].points[2].x, ligne_tab[i].points[2].y), cvScalar(0,(i==1)?255:0,255),4);
		cvLine(imgTracking, cvPoint(ligne_tab[i].points[2].x, ligne_tab[i].points[2].y), cvPoint(ligne_tab[i].points[3].x, ligne_tab[i].points[3].y), cvScalar(0,(i==1)?255:0,255),4);
		cvLine(imgTracking, cvPoint(ligne_tab[i].points[3].x, ligne_tab[i].points[3].y), cvPoint(ligne_tab[i].points[0].x, ligne_tab[i].points[3].y), cvScalar(0,(i==1)?255:0,255),4);
		ligne_tab[i].utilisee = false;
		
		if (i==0) 
		{
			if (lastY1-ligne_tab[0].posY>0) // Si on change de ligne (sur la même file)
			{ 
				time_span = duration_cast<duration<double>> (high_resolution_clock::now() - t12); // Calcul du temps
				t12 = high_resolution_clock::now(); // Prise du nouveau temps 
				vitesse_lue = taille_ligne/double(time_span.count())*3.6; //calcul de la vitesse taille_ligne(ligne+noir)/temps*conversion_M/S_Km/h

				if (vitesse_lue<moyenne_vitesse+100) //Calcul de la nouvelle moyenne de vitesse et affichage
				{  
					moyenne_vitesse = (moyenne_vitesse + vitesse_lue)/2;

					std::cout << "New line " << lastY1-ligne_tab[0].posY <<  " " << time_span.count() << " Vitesse : " << moyenne_vitesse << " Temps : " << temps << std::endl;
				}
			}
			lastY1 = ligne_tab[0].posY;
		}
		else if (i==1) 
		{
			if (lastY1-ligne_tab[1].posY>1)// Si on change de ligne (sur la même file) 
			{ 
				time_span = duration_cast<duration<double>> (high_resolution_clock::now() - t22); // Calcul du temps
				t22 = high_resolution_clock::now(); // Prise du nouveau temps 
				vitesse_lue = taille_ligne/double(time_span.count())*3.6; //calcul de la vitesse taille_ligne(ligne+noir)/temps*conversion_M/S_Km/h

				if (vitesse_lue<moyenne_vitesse+100) //Calcul de la nouvelle moyenne de vitesse et affichage 
				{ 
					moyenne_vitesse2 = (moyenne_vitesse2 + vitesse_lue)/2;
					std::cout << "New line " << lastY1-ligne_tab[1].posY <<  " " << time_span.count() << " Vitesse : " << moyenne_vitesse2 << " Temps : " << temps << std::endl;
				}
			}
			lastY1 = ligne_tab[1].posY;
		}
		moyenne_vitesseT = ( moyenne_vitesse + moyenne_vitesse2 )/2;
	}
}

  cvReleaseMemStorage(&storage);
}


void panneau(unsigned int xPos, unsigned int yPos) { //Affichage du panneau attention /!\ quand l'utilisateur va trop vite
	cvLine(imgTracking, cvPoint(xPos,yPos), cvPoint(xPos+30,yPos), cvScalar(0,0,255),2);
	cvLine(imgTracking, cvPoint(xPos,yPos), cvPoint(xPos+15,yPos-30), cvScalar(0,0,255),2);
	cvLine(imgTracking, cvPoint(xPos+15,yPos-30), cvPoint(xPos+30,yPos), cvScalar(0,0,255),2);

	cvLine(imgTracking, cvPoint(xPos+15,yPos-22), cvPoint(xPos+15,yPos-10), cvScalar(0,0,255),2);
	cvLine(imgTracking, cvPoint(xPos+15,yPos-5), cvPoint(xPos+15,yPos-5), cvScalar(0,0,255),2);

}


void traceGrille(IplImage* imgTracking) { //Affiche une grille sur l'écran
	for (unsigned int i=0; i<500; i+=100) {
		for (unsigned int j=0; j<1000; j+=100) {
			cvLine(imgTracking, cvPoint(j,0), cvPoint(j,1000), cvScalar(255,255,255),1);
		}
		cvLine(imgTracking, cvPoint(0,i), cvPoint(1000,i), cvScalar(255,255,255),1);
	}
}


//Fonction principale
int main(){
	
	/*
		Initialisations
	*/	
	
  	cvInitFont(&font,CV_FONT_HERSHEY_SIMPLEX, 1,1); // Initialisation de la police d'écriture
	int i=0;
  	int temps = 15; // temps d'attente entre deux frames
  	
  	cvNamedWindow("Video"); // Vidéo modifiée 
    
    cvNamedWindow("NB"); // Window noir et blanc
    
    cvNamedWindow("Control", CV_WINDOW_AUTOSIZE); // barettes de contrôle HSV
    
    IplImage* frame=0; //Contiendra une image de la vidéo
    
    
    //Chargement de la vidéo
    CvCapture *capture = cvCaptureFromAVI("b.mp4");

    if(!capture){
        printf("Capture failure\n");
        return -1;
    }
    
    frame = cvQueryFrame(capture); //On charge une frame       
    if(!frame) return -1;
   
    //create a blank image and assigned to 'imgTracking' which has the same size of original video
    imgTracking=cvCreateImage(cvGetSize(frame),IPL_DEPTH_8U, 3);
    
    cvZero(imgTracking); //passage en n&b

		
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

		trackObject(imgGrayScale, i, temps); // Recherche et affichage de tout les contours
		
		if (grid) traceGrille(imgTracking);

		//Affichage de la vidéo sur l'écran
		cvPutText (imgTracking,doubleToStr(int(moyenne_vitesseT)).c_str(),cvPoint(40,30), &font, cvScalar(0,(moyenne_vitesseT<=110)?255:0,(moyenne_vitesseT>110)?255:0)); //Affichage de la vitesse BGR
		if (moyenne_vitesseT>110) panneau(5,30);
		// Add the tracking image and the frame
		cvAdd(frame, imgTracking, frame); //On superpose les deux pour faire apparaitre les points

		cvSaveImage("test.jpg", frame); //Sortie de l'image
		imshow("Thresholded Image", imgThresholded); //show the thresholded image
		cvShowImage("Video", frame);
		
		
		/*
			Gestion des events
		*/
		
		
		int c = cvWaitKey(temps);//15 30 30 30

		if ((char)c==72 || (char)c==104) cvSaveImage("test2.jpg", frame);

        //Wait 10mS

        if ((char)c=='g' || (char)c=='G') grid=!grid; //affichage de la grille
        if ((char)c=='m') temps = 100; //accéléré
        if ((char)c=='l') temps =15; //vitesse normale
        if ((char)c=='p') temps =1; //ralentis
        if ((char)c=='o') temps =0; //pause ou pas à pas
        if((char)c==27 ) break;
        
        /*
        	Nettoyage
        */        
        
        cvZero(imgTracking); // Supprimer les autres points

		//Clean up used images
		cvReleaseImage(&imgGrayScale); // destruction des images         
		cvReleaseImage(&frame);
        
    }

    cvDestroyAllWindows();
    cvReleaseImage(&imgTracking);
    cvReleaseCapture(&capture);     

    return 0;
}
