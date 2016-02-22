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
{throw runtime_error("Pas de construction d'erreur par défaut");} /// Une erreur d"pend d'une action donc pas de constructeur par défaut.

Erreur::Erreur(string _texte)
:type_E(_texte)
{}


Erreur::~Erreur()
{}
