#include <cv.h>
#include <highgui.h>
#include <string>
#include <exception>

using namespace std;

#include "Element.hpp"

Element::Element()
:id(0), type("NaN")
{throw runtime_error("Pas de construction par défaut d'un élément");}

Element::Element(string _type)
:type(_type)
{}

Element::~Element()
{}

