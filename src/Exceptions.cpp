#include "Exceptions.hpp"

/*

AssemblerException::AssemblerException(){
	this->programAtom = NULL;
}
AssemblerException::AssemblerException(ProgramAtom* programAtom, string info){
	this->programAtom = programAtom;
	this->info = info;
}
string AssemblerException::ExceptionName = "AssemblerException";
string AssemblerException::toString(string lead){
	return 
		lead
		+ " error in file \"" 
		+ programAtom->programLine->fileName 
		+ "\" on line " 
		+ std::to_string(programAtom->programLine->lineNumber)
		+ ":\t" 
		+ programAtom->token;
}








FileNotFoundException::FileNotFoundException()
	:	AssemblerException()
{

}
FileNotFoundException::FileNotFoundException(ProgramAtom* programAtom, string info)
	:	AssemblerException(programAtom, info)
{

}
string FileNotFoundException::ExceptionName = "FileNotFoundException";
string FileNotFoundException::toString(){
	return AssemblerException::toString(ExceptionName);
}







UnexpectedTokenException::UnexpectedTokenException()
	:	AssemblerException()
{

}
UnexpectedTokenException::UnexpectedTokenException(ProgramAtom* programAtom, string info)
	:	AssemblerException(programAtom, info)
{

}
string UnexpectedTokenException::ExceptionName = "UnexpectedTokenException";
string UnexpectedTokenException::toString(){
	return AssemblerException::toString(ExceptionName);
}









ExpectedTokenException::ExpectedTokenException()
	:	AssemblerException()
{

}
ExpectedTokenException::ExpectedTokenException(ProgramAtom* programAtom, string info)
	:	AssemblerException(programAtom, info)
{

}
string ExpectedTokenException::ExceptionName = "ExpectedTokenException";
string ExpectedTokenException::toString(){
	return AssemblerException::toString(ExceptionName);
}













EncodingException::EncodingException()
	:	AssemblerException()
{

}
EncodingException::EncodingException(ProgramAtom* programAtom, string info)
	:	AssemblerException(programAtom, info)
{

}
string EncodingException::ExceptionName = "ExpectedTokenException";
string EncodingException::toString(){
	return AssemblerException::toString(ExceptionName);
}











*/
