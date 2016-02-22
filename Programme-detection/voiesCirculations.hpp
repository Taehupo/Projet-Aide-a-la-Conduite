/**
*\file voiesCirculations.hpp
*\author Gabriel Aubert - Johann Denoize - Etienne Dubuisson - Mathieu Terrier ;
*\details Cette classe permet la détection des voie de circulations
*\date 19 Février 2016
*/

#ifndef VOIECIRCULATION_HPP
#define VOIECIRCULATION_HPP

/**
* \class voieCirculation
* \brief Classe pour la fonction F3 "Détection des voies de circulation". \n
* Cette classe permet la détection de voie de circulation à partir des lignes
*/

class voieCirculation : pulic Element
{
private:
	Lane * ligne_1; 				/// Elle se compose d'une ligne détectée
	Lane * ligne_2; 				/// Et d'une autre ligne
	unsigned int ID;				/// D'une ID pour pouvoir reconnaitre quelle est cette voie
	static unsigned int tempID;		/// Une ID temporaire pour s'occuper des affectation & compter le nombre de lignes
	voieCirculation();				

public:
	voieCirculation(Lane*, Lane*);
	~voieCirculation();

	Lane * getLane1();
	Lane * getLane2();
	unsigned int getLaneID();

	//Quelquechose dessinerVoieCirculation(des params ?);

};

#endif