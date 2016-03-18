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

void traceGrille(IplImage* imgTracking)/// Cette fonction permet d'afficher un quadrillage sur la vidéo, on voit alors les différent carré ou l'ont peut détecté des éléments.\n Cela permet d'observer par exemple les zones de la détection des lignes.
{
	for (unsigned int i=0; i<500; i+=100) 
	{
	    for (unsigned int j=0; j<1000; j+=100) 
	    {
	     	cvLine(imgTracking, cvPoint(j,0), cvPoint(j,1000), cvScalar(255,255,255),1); // trace les lignes verticales
	    }
		cvLine(imgTracking, cvPoint(0,i), cvPoint(1000,i), cvScalar(255,255,255),1); // trace les lignes horizontales
	}
}

void OcvCore::trackObject(IplImage* imgThresh, int& ni, const int & temps)
{
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