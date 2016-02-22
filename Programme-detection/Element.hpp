/**
*\file Element.hpp
*\author Gabriel Aubert - Johann Denoize - Etienne Dubuisson - Mathieu Terrier ;
*\details C'est une classe centrale, hérité par les autres, elle permet d'avoir les bases pour les autres éléments.
*\date 22 Février 2016
*/

#ifndef ELEMENT_HPP
#define ELEMENT_HPP

typedef unsigned int uint;
/**
* \class Element
* \brief Classe Mére.\n
* Cette classe est la classe centrale des éléments détectés.
*/
class Element
{
private:
	uint id;		// Un élément sera composé d'un identifiant
	string type;	// Du texte, un entier, un son, une image, ...
	Element();

public:
	Element(string);
	~Element();
	
};

#endif