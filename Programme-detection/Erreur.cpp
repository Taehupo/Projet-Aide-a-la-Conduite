#include <cv.h>
#include <highgui.h>
#include <string>
#include <exception>

using namespace std;

#include "Erreur.hpp"

Erreur::Erreur()
:type_E("Erreur Invalide")
{throw runtime_error("Pas de construction d'erreur par défaut");}

Erreur::Erreur(string _texte)
:type_E(_texte)
{}


Erreur::~Erreur()
{}
