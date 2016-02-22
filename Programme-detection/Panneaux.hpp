/**
*\file laneDetection.hpp
*\author Gabriel Aubert - Johann Denoize - Etienne Dubuisson - Mathieu Terrier ;
*\details Cette classe permet la détection des lignes 
*\date 22 Février 2016
*/

#ifndef PANNEAUX_HPP
#define PANNEAUX_HPP

/**
* \class Panneaux
* \brief Classe pour la fonction F2 & F6 : "Détection des Panneaux".\n
* Cette classe permet la reconnaissance, la détection & l'enregistrement des Panneaux de circulation
* Elle hérite d'Element
*/

class Panneaux : public Element
{
public:
	Panneaux();
	~Panneaux();
	
};

#endif
