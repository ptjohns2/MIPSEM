#ifndef __EXCEPTIONS_HPP__
#define __EXCEPTIONS_HPP__

#include "Assembler.hpp"
#include "types.hpp"

#include <exception>
#include <string>


using std::exception;
using std::string;

class AssemblerException : public exception{
	public:
		AssemblerException();
		AssemblerException(ProgramLine*, string error, string offendingToken);

		string toString();
		
		const ProgramLine* programLine;
		const string info;
		const string offendingToken;

	protected:

};


class InvalidTokenException : public exception{
	public:
		InvalidTokenException();
		InvalidTokenException(string, string);

		string toString();

	protected:
		string type;
		string token;



};



#endif