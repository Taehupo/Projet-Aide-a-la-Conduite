/**
* \file laneDetection.cpp
* \author {Gabriel Aubert Johann Denoize Etienne Dubuisson Mathieu Terrier}
* \details Cette classe permet la détection des lignes 
*/
#include <cv.h>
#include <highgui.h>

using namespace std;

#include "laneDetection.hpp"


long long unsigned int Lane::tempID = 0; /*! Id temporaire initilisé à 0 permettant d'être donné au différente lignes détectés */

/**
* \brief Constreur et Constructeur de copie
*/
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

/**
* \brief Getter : renvoie x
*/
unsigned int Lane::getLaneX()
{
	return x;
}

/**
* \brief Getter : renvoie y
*/
unsigned int Lane::getLaneY()
{
	return y;
}

/**
* \brief Getter : renvoie l'ID
*/
long long unsigned int Lane::getLaneID()
{
	return ID;
}

/**
* \brief Setter : on modifie la valeur de x
*/
void Lane::setLaneX(unsigned int _x)
{
	x = _x;
}

/**
* \brief Setter : on modifie la valeur de y
*/
void Lane::setLaneY(unsigned int _y)
{
	y = _y;
}

/**
* \brief Code permettant la détection des lignes, le but et d'ajouter la valeurs obtenue et incrementer de 1 le total des valeurs
*/
void detecLane(IplImage* imgTresh)
{
	/** à compléter */
}