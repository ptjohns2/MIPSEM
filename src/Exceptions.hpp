#ifndef __EXCEPTIONS_HPP__
#define __EXCEPTIONS_HPP__

#include <exception>
#include <string>

#include "types.hpp"

using std::exception;
using std::string;

class ParserException : public exception{
	public:


	private:


};

class UnrecognizedTokenException : public ParserException{
	public:


	private:


};

class ExpectedTokenException : public ParserException{
	public:


	private:


};


class EncodingException : public exception{	
	public:
		string instruction;

	private:


};

class DecodingException : public exception{		
	public:
		instr instruction;

	private:


};



#endif