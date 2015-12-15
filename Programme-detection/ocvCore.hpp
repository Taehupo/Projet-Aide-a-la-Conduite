#ifndef OCVCORE_HPP
#define OCVCORE_HPP

class OcvCore {
public:
	OcvCore(std::string _fileName);
	~OcvCore();
	void filter();
	void getNewFrame();
	void showFrameWindow();
	void superpose (IplImage* _frame1, IplImage* _frame2);
private:

	std::string fileName;
	CvCapture * capture; //Vidéo

	IplImage* frame=0; //Une image de la vidéo
	IplImage* imgGrayScale; //Image noir/blanc

	IplImage* imgTracking=0; //Image sur laquelle on place les points qui désignent les lignes détectées (bleu et rouge)

};

#endif