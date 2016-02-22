/**
*\file laneDetection.hpp
*\author Gabriel Aubert - Johann Denoize - Etienne Dubuisson - Mathieu Terrier ;
*\details Cette classe est celle du flux vidéo
*\date 22 Février 2016
*/

#ifndef FLUX_HPP
#define FLUX_HPP


/**
* \class Flux
* \brief Classe pour contenir le flux vidéo.\n
* Cette classe d'accéder facilement au flux vidéo souhaité
*/

class Flux
{
private:
	char * filename; /// Nom du fichier qui serviras de flux (Se servir du fluc direct viendras après)
	Flux();
public:
	Flux(char *);
	~Flux();
	
};

#endif