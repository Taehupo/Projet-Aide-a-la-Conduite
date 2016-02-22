#ifndef ELEMENT_HPP
#define ELEMENT_HPP

typedef unsigned int uint;

class Element
{
private:
	uint id;
	string type;
	Element();

public:
	Element(string);
	~Element();
	
};

#endif