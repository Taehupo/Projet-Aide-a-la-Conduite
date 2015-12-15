#ifndef LANEDETECTION_HPP
#define LANEDETECTION_HPP

#include <cv.h>
#include <highgui.h>

class Lane 
{
private:
	unsigned int x,y;
	long long unsigned int ID;
	static long long unsigned int tempID = 0;

public:
	Lane(unsigned int, unsigned int);
	Lane();
	~Lane();
	
	unsigned int getLaneX();
	unsigned int getLaneY();
	long long unsigned int getLaneID();

	void setLaneX(unsigned int);
	void setLaneY(unsigned int);

	void detecLane(IplImage*);
};

#endif