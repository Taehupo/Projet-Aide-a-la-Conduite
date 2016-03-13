/**
*\author Gabriel Aubert - Johann Denoize - Etienne Dubuisson - Mathieu Terrier ;
*\date 19 Février 2016
*/
#include <cv.h>
#include <highgui.h>

using namespace std;

#include "laneDetection.hpp"


long long unsigned int Lane::tempID = 0; /*! Id temporaire initilisé à 0 permettant d'être donné au différente lignes détectés */

Lane::Lane(unsigned int _x, unsigned int _y)
:x(_x), y(_y)
{
	ID = tempID; 				/*! On affecte l'id temporaire a l'id */
	tempID = ++tempID;			/*! On incremente l'id temporaire de 1 pour la prochaine ligne */
}

Lane::Lane()
{
	x = 0;						/*! la ligne x est initilisé à 0 par défaut */
	y = 0;						/*! la ligne y est initilisé à 0 par défaut */
	ID = tempID;				/*! On affecte l'id temporaire a l'id */
	tempID = ++tempID;			/*! On incremente l'id temporaire de 1 pour la prochaine ligne */
}

Lane::~Lane()
{}

unsigned int Lane::getLaneX()
{
	return x; /*! renvoie x */
}

unsigned int Lane::getLaneY()
{
	return y; /*! renvoie y */
}

long long unsigned int Lane::getLaneID()
{
	return ID; /*! renvoie l'ID de la ligne */
}

void Lane::setLaneX(unsigned int _x)
{
	x = _x; /*! Modifiation de x */
}

void Lane::setLaneY(unsigned int _y)
{
	y = _y; /*! Modifiation de y */
}

void Lane::detecLane(IplImage* imgTresh)
{
	/*! Permet de détecter les lignes : celle de droite et celle de gauche, sur une image.*/
	/*! fonction à compléter : supprimer ce commentaire un fois remplit */
}

double Lane::distance2pt (CvPoint* p0, CvPoint* p1)
{ 
	return sqrt(pow(p0->x - p1->x, 2) + pow(p0->y - p1->y,2)); /*! Distance entre deux points*/
}

void Lane::swapCvPoint (CvPoint * p1, CvPoint * p2) 
{
	CvPoint tmp = *p1;
	*p1 = *p2;
	*p2 = tmp;
}

bool Lane::ligne (CvPoint *pt[4])
{
	/*! Permet de detecter la ligne ? */
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
