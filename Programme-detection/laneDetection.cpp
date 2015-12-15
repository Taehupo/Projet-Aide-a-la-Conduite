#include <cv.h>
#include <highgui.h>

using namespace std;

#include "laneDetection.hpp"

long long unsigned int Lane::tempID = 0;

Lane::Lane(unsigned int _x, unsigned int _y)
:x(_x), y(_y)
{
	ID = tempID;
	tempID = ++tempID;
}

Lane::Lane()
{
	x = 0;
	y = 0;
	ID = tempID;
	tempID = ++tempID;
}

Lane::~Lane()
{}

unsigned int Lane::getLaneX()
{
	return x;
}

unsigned int Lane::getLaneY()
{
	return y;
}

long long unsigned int Lane::getLaneID()
{
	return ID;
}

void Lane::setLaneX(unsigned int _x)
{
	x = _x;
}

void Lane::setLaneY(unsigned int _y)
{
	y = _y;
}

void detecLane(IplImage* imgTresh)
{
	//à compléter
}