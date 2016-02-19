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

void detecLane(IplImage* imgTresh)
{
	/*! Permet de détecter les lignes : celle de droite et celle de gauche, sur une image.*/
	/*! fonction à compléter : supprimer ce commentaire un fois remplit */
}