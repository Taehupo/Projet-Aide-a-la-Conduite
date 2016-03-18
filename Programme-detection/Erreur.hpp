/**
*\file Erreur.hpp
*\author Gabriel Aubert - Johann Denoize - Etienne Dubuisson - Mathieu Terrier ;
*\details Cette classe permet l'affichage d'erreur textuel ou sonore pour prevenir le conducteurs et attirer son attention
*\date 22 Février 2016
*/
#ifndef ERREUR_HPP
#define ERREUR_HPP
/**
* \class Erreur
* \brief Classe répondant à la fonction : F9 : Avertissements écrits et sonores.\n
* Cette classe affiche les erreurs textuel et sonore : par exemple le depassement de la vitesse du véhicule entraine l'affiche de la vitesse en rouge, une icône attention, et un bip sonore.\n
* Cette classe ne traite pas les exceptions.
*/
class Erreur : public Element
{
private:
	string type_E;	// L'erreur rencontrer aura un nom
	unsigned int xPos, yPos; /// Cette classe prend 2 insigned int pour positionner les messages textuels
	double vr; // la vitesse (sous forme d'un double) est récupérée pour convertion en string 
	Erreur();
public:
	Erreur(string, unsigned int, unsigned int, double);
	~Erreur();
	
	void affichePVR(unsigned int xPos, unsigned int yPos);
	const string doubleToStr(double vr);
};

#endif