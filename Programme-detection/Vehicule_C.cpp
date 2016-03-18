/**
*\author Gabriel Aubert - Johann Denoize - Etienne Dubuisson - Mathieu Terrier ;
*\date 22 Février 2016
*/
#include <cv.h>
#include <highgui.h>
#include <string>
#include <exception>

using namespace std;

#include "Vehicule_C.hpp"

Vehicule_C::Vehicule_C()
{
	/// Construteur à réaliser
}

Vehicule_C::~Vehicule_C()
{
	/// Destructeur à réaliser
}

void avgSpeed()
{
	cout << "avgSpeed" << endl;
  avg=0;
  for (unsigned int i=0; i<3; ++i) /// on prend les 3 derniere frame pour le calcul de la vitesse si j'ai bient suivit
    avg += vitesse[i];
  avg/=3;
  //cout << "avg  "<<avg;
}