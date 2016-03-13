/**
*\file myException.hpp
*\author Gabriel Aubert - Johann Denoize - Etienne Dubuisson - Mathieu Terrier ;
*\details Cette classe permet la gestion des exceptions
*\date 24 Février 2016
*/

#ifndef MYEXCEPTION_HPP
#define MYEXCEPTION_HPP
/**
* \class myException
* \brief Une classe d'exception. \n
* Cette classe permet d'attraper et de gérer les exceptions.
*/
class myException : public exception

{
private:

public:
	myException();
	~myException();
};

#endif