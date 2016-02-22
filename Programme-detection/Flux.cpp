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
}

Flux::Flux(char * _filename)
:filename(_filename)
{}

Flux::~Flux()
{delete filename;}