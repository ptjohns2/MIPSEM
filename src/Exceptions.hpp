#ifndef __EXCEPTIONS_HPP__
#define __EXCEPTIONS_HPP__

#include "Assembler.hpp"

#include <exception>
#include <string>


using std::exception;
using std::string;

class AssemblerException : public exception{
	public:
		AssemblerException();
		AssemblerException(string);

		string toString();

	protected:
		string info;

};





#endif