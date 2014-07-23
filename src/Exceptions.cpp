#include "Exceptions.hpp"



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
	ExceptionName = "FileNotFoundException";
}
FileNotFoundException::FileNotFoundException(ProgramAtom* programAtom, string info)
	:	AssemblerException(programAtom, info)
{
	ExceptionName = "FileNotFoundException";
}
string FileNotFoundException::toString(){
	return AssemblerException::toString(ExceptionName);
}







UnexpectedTokenException::UnexpectedTokenException()
	:	AssemblerException()
{
	ExceptionName = "UnexpectedTokenException";
}
UnexpectedTokenException::UnexpectedTokenException(ProgramAtom* programAtom, string info)
	:	AssemblerException(programAtom, info)
{
	ExceptionName = "UnexpectedTokenException";
}
string UnexpectedTokenException::toString(){
	return AssemblerException::toString(ExceptionName);
}









ExpectedTokenException::ExpectedTokenException()
	:	AssemblerException()
{
	ExceptionName = "ExpectedTokenException";
}
ExpectedTokenException::ExpectedTokenException(ProgramAtom* programAtom, string info)
	:	AssemblerException(programAtom, info)
{
	ExceptionName = "ExpectedTokenException";
}
string ExpectedTokenException::toString(){
	return AssemblerException::toString(ExceptionName);
}













EncodingException::EncodingException()
	:	AssemblerException()
{
	ExceptionName = "EncodingException";
}
EncodingException::EncodingException(ProgramAtom* programAtom, string info)
	:	AssemblerException(programAtom, info)
{
	ExceptionName = "EncodingException";
}
string EncodingException::toString(){
	return AssemblerException::toString(ExceptionName);
}












