/*!
* \file laneDetection.cpp
* \author Gabriel Aubert Johann Denoize Etienne Dubuisson Mathieu Terrier
*/
#include <cv.h>
#include <highgui.h>

using namespace std;

#include "laneDetection.hpp"

long long unsigned int Lane::tempID = 0; /*! Id temporaire initilisé à 0 permettant d'être donné au différente lignes détectés */

////////
// Constructeur et constructeur de copie de la classe laneDetection.hpp
////////
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

///////////
// Getter et Setter de la classe LaneDetection.hpp permettant de recuperer les valeurs de X Y et ID et de modifier X et Y
///////////
unsigned int Lane::getLaneX()
{
	return x;
}

unsigned int Lane::getLaneY()
{
	return y;
}

long long unsigned int Lane::getLaneID()
{
	return ID;
}

void Lane::setLaneX(unsigned int _x)
{
	x = _x;
}

void Lane::setLaneY(unsigned int _y)
{
	y = _y;
}

/*!
* Code permettant la détection des lignes, le but et d'ajouter la valeurs obtenue et incrementer de 1 le total des valeurs
*/
void detecLane(IplImage* imgTresh)
{
	/*! à compléter */
}