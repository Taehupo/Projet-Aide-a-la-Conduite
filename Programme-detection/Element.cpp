/**
*\author Gabriel Aubert - Johann Denoize - Etienne Dubuisson - Mathieu Terrier ;
*\date 22 Février 2016
*/
#include <cv.h>
#include <highgui.h>
#include <string>
#include <exception>

using namespace std;

#include "Element.hpp"

Element::Element()
:id(0), type("NaN")
{throw runtime_error("Pas de construction par défaut d'un élément");} /// Constructeur par défaut interdit

Element::Element(string _type)
:type(_type)
{}

Element::~Element()
{}

