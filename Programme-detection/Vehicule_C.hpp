/**
*\file Vehicule_C.hpp
*\author Gabriel Aubert - Johann Denoize - Etienne Dubuisson - Mathieu Terrier ;
*\details Cette classe affiche les informations liées au véhicule de l'utilisateur
*\date 22 Février 2016
*/
#ifndef VEHICULEC_HPP
#define VEHICULEC_HPP
/**
* \class Vehicule_C
* \brief Classe répondant aux fonctions : F3 : Détermination de voies de circulation, F4 : Détermination de la vitesse du véhicule et F8 : Détection des distances de sécurité.\n
* Cette classe permetra d'afficher les informations liée au véhicule de l'utilisateur.
*/
class Vehicule_C : public Element
{
private:
	double vitesse [3] = {100}; // à améliorer
public:
	Vehicule_C();
	~Vehicule_C();
	
	void avgSpeed() /// Ancienne fonction qui doit permetre de calculer la vitesse de notre véhicule.
};

#endif