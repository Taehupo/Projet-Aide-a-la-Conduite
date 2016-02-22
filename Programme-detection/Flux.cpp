/**
*\author Gabriel Aubert - Johann Denoize - Etienne Dubuisson - Mathieu Terrier ;
*\date 22 Février 2016
*/

#include <cv.h>
#include <highgui.h>
#include <string>
#include <exception>

using namespace std;

#include "Flux.hpp"

Flux::Flux()
:filename("NOPE")
{
	throw runtime_error("Pas de construction de flux par défaut");
	///Construction par défaut interdite pour l'instant
}

Flux::Flux(char * _filename)
:filename(_filename)
{
	///Constructeur de la classe Flux, prend en paramètre un char * (nom du fichier vidéo, entre double quotes)
}

Flux::~Flux()
{
	delete filename;
	///Destructeur du flux, rend la mémoire alouée pour le filename
}