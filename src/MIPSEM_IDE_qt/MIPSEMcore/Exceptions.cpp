#include "Exceptions.hpp"



AssemblerException::AssemblerException(){}
AssemblerException::AssemblerException(ProgramLine programLine, string info, string offendingToken)
	:	programLine(programLine), info(info), offendingToken(offendingToken)
{

}

string AssemblerException::toString(){
	string message = "Error";
	message += " ["
		+ programLine.fileName
		+ ": line "
		+ std::to_string(programLine.lineNumber)
		+ "] ";

	message += this->info;
	message += ": \"" + this->offendingToken + "\"";
	return message;
}


InvalidTokenException::InvalidTokenException(){

}
InvalidTokenException::InvalidTokenException(string type, string token){
	this->type = type;
	this->token = token;
}

string InvalidTokenException::toString(){
	return "InvalidTokenException:\t\"" + token + "\" is not a \"" + type + "\"";
}



