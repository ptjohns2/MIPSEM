#include "Exceptions.hpp"



AssemblerException::AssemblerException(){

}
AssemblerException::AssemblerException(string info){
	this->info = info;
}

string AssemblerException::toString(){
	return "Error:\t" + info;
}








