/**
*\file laneDetection.cpp
*\author Gabriel Aubert Johann Denoize Etienne Dubuisson Mathieu Terrier
*\details Cette classe permet la détection des lignes 
*\date 19 Février 2016
*/

#ifndef LANEDETECTION_HPP
#define LANEDETECTION_HPP

#include <cv.h>
#include <highgui.h>

/**
* \class Lane
* \brief Classe pour la fonction F1 : Détection et lecture des lignes
* Cette classe permet la reconnaissance et la détection des lignes
*/
class Lane 
{
private:
	unsigned int x,y;							/** Elle se compose de 2 entier non signed x et y qui correspondent à la ligne droite et la ligne gauche */
	long long unsigned int ID;					/** Un identifiant associé à chaque ligne */
	static long long unsigned int tempID;		/** Un identifiant temporaire associée a une ligne */

public:
	Lane(unsigned int, unsigned int);
	Lane();
	~Lane();
	
	unsigned int getLaneX();
	unsigned int getLaneY();
	long long unsigned int getLaneID();

	void setLaneX(unsigned int);
	void setLaneY(unsigned int);

	void detecLane(IplImage*);
};



#endif