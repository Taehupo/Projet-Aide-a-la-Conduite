/**
*\file voiesCirculations.hpp
*\author Gabriel Aubert - Johann Denoize - Etienne Dubuisson - Mathieu Terrier ;
*\details Cette classe permet la détection des voie de circulations
*\date 19 Février 2016
*/

#ifndef VOIECIRCULATION_HPP
#define VOIECIRCULATION_HPP

/**
* \class VoieC
* \brief Classe pour la fonction F1 : "Détection et lecture des lignes" et F3 : "Détermination de voies de circulation".\n
* Cette classe permet la reconnaissance et la détection des lignes
*/
class voieCirculation
{
private:
	Lane * ligne_1;						/*! Elle ce compose de 2 lignes, correspondant au voie de circulation */
	Lane * ligne_2;
	unsigned int ID;					/*! Un identifiant associé à chaque ligne */
	static unsigned int tempID; 		/*! Un identifiant temporaire associée a une ligne */
	voieCirculation();					/*! Constructeur privé car on ne veut pas l'utiliser*/

public:
	voieCirculation(Lane*, Lane*);
	~voieCirculation();

	Lane * getLane1();
	Lane * getLane2();
	unsigned int getLaneID();

	//Quelquechose dessinerVoieCirculation(des params ?);

};

#endif