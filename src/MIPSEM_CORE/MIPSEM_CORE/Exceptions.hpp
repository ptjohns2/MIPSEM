#ifndef __EXCEPTIONS_HPP__
#define __EXCEPTIONS_HPP__

#include "Assembler.hpp"
#include "types.hpp"

#include <exception>
#include <string>

#define ERROR_UNRECOGNIZED_TOKEN		("Unrecognized token")
#define ERROR_UNRECOGNIZED_DIRECTIVE	("Unrecognized directive")
#define ERROR_UNRECOGNIZED_LABEL		("Label not recognized")
#define ERROR_INVALID_STRING_LITERAL	("Invalid string literal")
#define ERROR_INVALID_ALIGNMENT_VALUE	("Unable to align memory to non-fixed point number of bytes")
#define ERROR_INVALID_SPACE_VALUE		("Unable to reserve memory space of non-fixed point size")
#define ERROR_INVALID_LABEL				("Duplicate label")
#define ERROR_INVALID_LITERAL			("Invalid literal")
#define ERROR_INVALID_IMMEDIATE_LI		("Invalid immediate on \"li\" pseudoinstruction")
#define ERROR_INVALID_INSTRUCTION		("Unable to encode instruction")
#define ERROR_INVALID_PSEUDOINSTRUCTION	("Unable to translate pseudoinstruction")
#define ERROR_EXPECTED_END_MACRO        ("Expected .end_macro directive before EOF")

using std::exception;
using std::string;

class AssemblerException : public exception{
	public:
        AssemblerException();
		AssemblerException(ProgramLine, string error, string offendingToken);

		string toString();
		
		ProgramLine programLine;
		string info;
		string offendingToken;
        

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
