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
			+ "\: line "
			+ std::to_string(programLine->lineNumber)
			+ "]";
	}
	message += ":\t" + this->info;
	return message;
}








