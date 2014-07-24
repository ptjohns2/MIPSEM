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
		AssemblerException(ProgramAtom*, string);

		virtual string toString(string lead = ExceptionName);

	protected:
		static string ExceptionName;
		ProgramAtom* programAtom;
		string info;

};

class FileNotFoundException : public AssemblerException{
	public:
		FileNotFoundException();
		FileNotFoundException(string);

		string toString();

	private:

};



class UnexpectedTokenException : public AssemblerException{
	public:
		UnexpectedTokenException();
		UnexpectedTokenException(ProgramAtom*, string);

		string toString();

	private:

};

class ExpectedTokenException : public AssemblerException{
	public:
		ExpectedTokenException();
		ExpectedTokenException(ProgramAtom*, string);

		string toString();

	private:

};


class EncodingException : public AssemblerException{	
	public:
		EncodingException();
		EncodingException(ProgramAtom*, string);

		string toString();

	private:

};




#endif