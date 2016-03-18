/**
*\author Gabriel Aubert - Johann Denoize - Etienne Dubuisson - Mathieu Terrier ;
*\date 19 Février 2016
*/

#include <cv.h>
#include <highgui.h>

using namespace std;

#include "laneDetection.hpp"
#include "voiesCirculations.hpp"

unsigned int tempID = 0; /// ID temporaire initialisée

voieCirculation::voieCirculation()
:ligne_1(NULL), ligne_2(NULL)
{throw runtime_error "Pas de construction par défaut de voie de circualtion";} /// La construction par défaut est interdite

voieCirculation::voieCirculation(Lane * _ligne_1, Lane * _ligne_2)
:ligne_1(_ligne_1), ligne_2(_ligne_2)
{
	ID = tempID; /// On affecte à la voie l'ID temporaire
	tempID = tempID++; /// On incrémente l'ID temporaire pour garder le compte
}

voieCirculation::~voieCirculation()
{}

Lane * voieCirculation::getLane1()
{
	return ligne_1; /// Renvoie un pointeur vers la première ligne de la voie
} 

Lane * voieCirculation::getLane2()
{
	return ligne_2; /// Renvoie un pointeur vers la deuxième ligne de la voie
} 

unsigned int voieCirculation::getLaneID()
{
	return ID; /// Renvoie l'ID de la voie de circulation
}