/**
*\author Gabriel Aubert - Johann Denoize - Etienne Dubuisson - Mathieu Terrier ;
*\date 22 Février 2016
*/
#include <cv.h>
#include <highgui.h>
#include <stdio.h>
#include <time.h>
#include <chrono>
#include <ctime>
#include <ratio>

#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <exception>

using namespace std;
using namespace std::chrono;
using namespace cv;

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