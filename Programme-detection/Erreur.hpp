#ifndef Erreur
#define Erreur

// C'est la classe des erreur qu'on affiche à l'écran
// PAS DES EXCEPTIONS ! On la feras plus TARD !

class Erreur : public Element
{
private:
	string type_E;
	Erreur();
public:
	Erreur(string);
	~Erreur();
	
};

#endif