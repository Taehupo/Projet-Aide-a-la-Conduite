#include <cv.h>
#include <highgui.h>

using namespace std;

#include "laneDetection.hpp"
#include "voiesCirculations.hpp"

unsigned int tempID = 0;

voieCirculation::voieCirculation()
:ligne_1(NULL), ligne_2(NULL)
{throw "Pas de construction par défaut de voie de circualtion"}

voieCirculation::voieCirculation(Lane * _ligne_1, Lane * _ligne_2)
:ligne_1(_ligne_1), ligne_2(_ligne_2)
{
	ID = tempID;
	tempID = tempID++;
}

voieCirculation::~voieCirculation()
{}

Lane * voieCirculation::getLane1()
{return ligne_1;}

Lane * voieCirculation::getLane2()
{return ligne_2;}

unsigned int voieCirculation::getLaneID()
{return ID;}