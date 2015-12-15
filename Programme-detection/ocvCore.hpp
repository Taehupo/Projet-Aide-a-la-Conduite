#ifndef OCVCORE_HPP
#define OCVCORE_HPP

class OcvCore {
public:
	OcvCore(std::string _fileName);
	~OcvCore();
	void filter();
	void getNewFrame();
	void showFrameWindow(std::string _titre);
private:
	std::string fileName;
	CvCapture * capture; //Vidéo

	IplImage* frame=0; //Une image de la vidéo
	IplImage* imgGrayScale;

	IplImage* imgTracking=0;

};

#endif