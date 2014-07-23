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
		FileNotFoundException(ProgramAtom*, string);
		~FileNotFoundException();

		string toString();

	private:

};



class UnexpectedTokenException : public AssemblerException{
	public:
		UnexpectedTokenException();
		UnexpectedTokenException(ProgramAtom*, string);
		~UnexpectedTokenException();

		string toString();

	private:

};

class ExpectedTokenException : public AssemblerException{
	public:
		ExpectedTokenException();
		ExpectedTokenException(ProgramAtom*, string);
		~ExpectedTokenException();

		string toString();

	private:

};


class EncodingException : public AssemblerException{	
	public:
		EncodingException();
		EncodingException(ProgramAtom*, string);
		~EncodingException();

		string toString();

	private:

};




#endif