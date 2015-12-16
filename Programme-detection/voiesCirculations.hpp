#ifndef VOIECIRCULATION_HPP
#define VOIECIRCULATION_HPP

class voieCirculation
{
private:
	Lane * ligne_1;
	Lane * ligne_2;
	unsigned int ID;
	static unsigned int tempID;
	voieCirculation();

public:
	voieCirculation(Lane*, Lane*);
	~voieCirculation();

	Lane * getLane1();
	Lane * getLane2();
	unsigned int getLaneID();

	//Quelquechose dessinerVoieCirculation(des params ?);

};

#endif