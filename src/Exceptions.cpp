#include "Exceptions.hpp"



AssemblerException::AssemblerException(){

}
AssemblerException::AssemblerException(ProgramLine* programLine, string info){
	this->programLine = programLine;
	this->info = info;
}

string AssemblerException::toString(){
	string message = "Error";
	if(this->programLine != NULL){
		message += " [\""
			+ programLine->fileName
			+ "\": line "
			+ std::to_string(programLine->lineNumber)
			+ "]";
	}
	message += ":\t" + this->info;
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



