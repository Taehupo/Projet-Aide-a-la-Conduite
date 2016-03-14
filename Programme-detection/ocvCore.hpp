/**
*\file ocvCore.hpp
*\author Gabriel Aubert - Johann Denoize - Etienne Dubuisson - Mathieu Terrier ;
*\details Cette classe est la pour l'analyse de la vidéo et sont rendu
*\date 19 Février 2016
*/

#ifndef OCVCORE_HPP
#define OCVCORE_HPP

/**
* \class OcvCore
* \brief Classe pour la vidéo.\n
* Cette classe permet la reconnaissance et la détection des lignes.
*/
// Structure S_Ligne nécéssaire à trackObject()
typedef struct {
	CvPoint points[4];
	int posX, posY;
	bool utilisee = false;
} S_Ligne;

class OcvCore {
public:

	OcvCore(std::string _fileName);
	~OcvCore();
	void filter();
	void getNewFrame();
	void showFrameWindow();
	void superpose (IplImage* _frame1, IplImage* _frame2);
	void traceGrille(IplImage* imgTracking);
	// Ajout proto2
	void trackObject(IplImage* imgThresh, int& ni, const int & temps); // Permet la détéction de l'ensemble des éléments : lignes, panneaux
private:
	std::string fileName;
	CvCapture * capture; 				// Vidéo

	IplImage* frame=0; 					// Une image de la vidéo
	IplImage* imgGrayScale; 			// Image noir/blanc

	IplImage* imgTracking=0; 			// Image sur laquelle on place les points qui désignent les lignes détectées (bleu et rouge)
	// ajout proto2
	double centrey = 300;						/*! Position initiale du centre (entre deux lignes) */
	S_Ligne ligne_tab[2];						/*! tableau de S_ligne : structure plus haut */
	duration<double> time_span;					// Sert a tackobject, ne sais pas ou mettre
	high_resolution_clock::time_point t12, t22;	// Sert aussi a track Object, mesure du temps, pour les frames ?
	float taille_ligne = 13;					/*! Taille d'une bande */
	/// Moyenne de la vitesse obtenue  grace a la vitesse lue, par l'addition de moyenne_vitesse et moyenne_vitesse2 pour obtenir la vitesse finale
	double vitesse_lue;							/*! Vitesse lue par le programme */
	double moyenne_vitesse = 1;
	double moyenne_vitesse2 = 1;				
	double moyenne_vitesseT = 1;
	int lastY1 = -1;							/*! Le seul et l'unique */
};			

#endif