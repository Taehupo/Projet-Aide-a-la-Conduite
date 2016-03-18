/**
*\author Gabriel Aubert - Johann Denoize - Etienne Dubuisson - Mathieu Terrier ;
*\date 22 Février 2016
*/
#include <cv.h>
#include <highgui.h>
#include <string>
#include <exception>

using namespace std;

#include "Erreur.hpp"

Erreur::Erreur()
:type_E("Erreur Invalide")
{throw runtime_error("Pas de construction d'erreur par défaut");} /// Une erreur dépend d'une action donc pas de constructeur par défaut.

Erreur::Erreur(string _texte, unsigned int _x, unsigned int _y, double v)
:type_E(_texte), xPos(_x), yPos(_y), vr(v)
{}


Erreur::~Erreur()
{}

void affichePVR(unsigned int xPos, unsigned int yPos, IplImage * imgTracking) /// Permet d'afficher une icone attention a coté de la vitesse si le conducteur vient a dépasser la vitesse limite du derniere panneau de vitesse détecté.
{
	cvLine(imgTracking, cvPoint(xPos,yPos), cvPoint(xPos+30,yPos), cvScalar(0,0,255),2);
  	cvLine(imgTracking, cvPoint(xPos,yPos), cvPoint(xPos+15,yPos-30), cvScalar(0,0,255),2);
  	cvLine(imgTracking, cvPoint(xPos+15,yPos-30), cvPoint(xPos+30,yPos), cvScalar(0,0,255),2);

  	cvLine(imgTracking, cvPoint(xPos+15,yPos-22), cvPoint(xPos+15,yPos-10), cvScalar(0,0,255),2);
 	cvLine(imgTracking, cvPoint(xPos+15,yPos-5), cvPoint(xPos+15,yPos-5), cvScalar(0,0,255),2);
}

const string doubleToStr(double vr) /// Permet l'affichage de la vitesse du véhicule du conducteur
{
	stringstream ss;
 	 ss << xPos;
  	return ss.str(); /// renvoie le la vitesse du véhicule en une chaine de caractère
}